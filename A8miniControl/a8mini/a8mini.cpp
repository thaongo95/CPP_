#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>

#include <arpa/inet.h>
#include <unistd.h>

class SiyiCamera
{
public:
    SiyiCamera(std::string ip="192.168.144.25", int port=37260)
    {
        this->ip = ip;
        this->port = port;
        sock = -1;
        seq = 0;
        running = false;
    }

    // ---------------- CRC16 ----------------
    uint16_t crc16_siyi(const std::vector<uint8_t>& data)
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

                crc &= 0xFFFF;
            }
        }

        return crc;
    }

    // ---------------- Packet Builder ----------------
    std::vector<uint8_t> build_packet(uint8_t cmd_id,
                                      const std::vector<uint8_t>& data = {})
    {
        std::vector<uint8_t> packet;

        packet.push_back(0x55);
        packet.push_back(0x66);

        packet.push_back(0x01); // CTRL

        uint16_t len = data.size();

        packet.push_back(len & 0xFF);
        packet.push_back((len >> 8) & 0xFF);

        packet.push_back(seq & 0xFF);
        packet.push_back((seq >> 8) & 0xFF);

        packet.push_back(cmd_id);

        packet.insert(packet.end(), data.begin(), data.end());

        uint16_t crc = crc16_siyi(packet);

        packet.push_back(crc & 0xFF);
        packet.push_back((crc >> 8) & 0xFF);

        seq = (seq + 1) % 65536;

        return packet;
    }

    // ---------------- Connect ----------------
    bool connectCamera()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0)
        {
            std::cout << "Socket creation failed\n";
            return false;
        }

        sockaddr_in server{};
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        inet_pton(AF_INET, ip.c_str(), &server.sin_addr);

        if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0)
        {
            std::cout << "Connection failed\n";
            return false;
        }

        running = true;

        std::cout << "Connected to SIYI camera\n";

        heartbeatThread = std::thread(&SiyiCamera::heartbeat_loop, this);

        return true;
    }

    // ---------------- Heartbeat ----------------
    void heartbeat_loop()
    {
        std::vector<uint8_t> packet =
        {0x55,0x66,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x59,0x8B};

        while (running)
        {
            send(sock, packet.data(), packet.size(), 0);

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    // ---------------- Send Command ----------------
    void send_cmd(uint8_t cmd_id,
                  const std::vector<uint8_t>& data = {})
    {
        auto packet = build_packet(cmd_id, data);

        std::cout << "TX: ";

        for (auto b : packet)
            printf("%02X ", b);

        std::cout << std::endl;

        send(sock, packet.data(), packet.size(), 0);

        uint8_t buffer[1024];

        int len = recv(sock, buffer, sizeof(buffer), 0);

        if (len > 0)
        {
            std::cout << "RX: ";

            for (int i=0;i<len;i++)
                printf("%02X ", buffer[i]);

            std::cout << std::endl;
        }
    }

    // ---------------- Format SD ----------------
    void format_sd()
    {
        std::cout << "Formatting SD card\n";
        send_cmd(0x48);
    }

    // ---------------- Disconnect ----------------
    void closeCamera()
    {
        running = false;

        if (heartbeatThread.joinable())
            heartbeatThread.join();

        if (sock >= 0)
            close(sock);

        std::cout << "Disconnected\n";
    }

private:
    std::string ip;
    int port;

    int sock;
    uint16_t seq;

    bool running;

    std::thread heartbeatThread;
};
