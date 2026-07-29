#include "siyi_camera.h"

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

SiyiCamera::SiyiCamera(std::string ip, int port)
    : ip_(ip), port_(port), sock_(-1), running_(false), seq_(0)
{
}

SiyiCamera::~SiyiCamera()
{
    closeCamera();
}

uint16_t SiyiCamera::crc16(const std::vector<uint8_t>& data)
{
    uint16_t crc = 0x0000;
    uint16_t poly = 0x1021;

    for (uint8_t byte : data)
    {
        crc ^= (byte << 8);

        for (int i = 0; i < 8; i++)
        {
            if (crc & 0x8000)
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;
        }
    }

    return crc;
}

std::vector<uint8_t> SiyiCamera::buildPacket(uint8_t cmdId, const std::vector<uint8_t>& data)
{
    std::vector<uint8_t> packet;

    packet.push_back(0x55);
    packet.push_back(0x66);

    packet.push_back(0x01);   // CTRL need ack

    uint16_t len = data.size();
    packet.push_back(len & 0xFF);
    packet.push_back(len >> 8);

    packet.push_back(seq_ & 0xFF);
    packet.push_back(seq_ >> 8);

    packet.push_back(cmdId);

    packet.insert(packet.end(), data.begin(), data.end());

    uint16_t crc = crc16(packet);

    packet.push_back(crc & 0xFF);
    packet.push_back(crc >> 8);

    seq_++;

    return packet;
}

bool SiyiCamera::connectCamera()
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_ < 0)
    {
        std::cout << "Socket create failed\n";
        return false;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);

    inet_pton(AF_INET, ip_.c_str(), &addr.sin_addr);

    if (::connect(sock_, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        std::cout << "Connect failed\n";
        return false;
    }

    std::cout << "Connected to SIYI camera\n";

    running_ = true;
    heartbeatThread_ = std::thread(&SiyiCamera::heartbeatLoop, this);

    return true;
}

void SiyiCamera::heartbeatLoop()
{
    std::vector<uint8_t> hb =
    {0x55,0x66,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x59,0x8B};

    while (running_)
    {
        send(sock_, hb.data(), hb.size(), 0);
        sleep(1);
    }
}

void SiyiCamera::sendCommand(uint8_t cmdId, const std::vector<uint8_t>& data)
{
    auto packet = buildPacket(cmdId, data);

    std::cout << "TX: ";
    for (auto b : packet)
        printf("%02X ", b);
    std::cout << std::endl;

    send(sock_, packet.data(), packet.size(), 0);

    uint8_t buffer[1024];

    int n = recv(sock_, buffer, sizeof(buffer), MSG_DONTWAIT);

    if (n > 0)
    {
        std::cout << "RX: ";
        for (int i = 0; i < n; i++)
            printf("%02X ", buffer[i]);
        std::cout << std::endl;
    }
}

void SiyiCamera::formatSD()
{
    std::cout << "Formatting SD\n";
    sendCommand(0x48);
}

void SiyiCamera::closeCamera()
{
    running_ = false;

    if (heartbeatThread_.joinable())
        heartbeatThread_.join();

    if (sock_ > 0)
        close(sock_);

    std::cout << "Disconnected\n";
}
