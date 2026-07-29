#include "siyi_camera.h"

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

SiyiCamera::SiyiCamera(std::string ip, int port)
    : ip_(ip), port_(port), sock_(-1)
{
    for (const auto& s : upstr)
        upPackets.push_back(hexToBytes(s));

    for (const auto& s : downstr)
        downPackets.push_back(hexToBytes(s));

    for (const auto& s : leftstr)
        leftPackets.push_back(hexToBytes(s));

    for (const auto& s : rightstr)
        rightPackets.push_back(hexToBytes(s));

    for (const auto& s : zoomstr)
        zoomPackets.push_back(hexToBytes(s));
    stopPacket = hexToBytes(stopstr);
    homePacket = hexToBytes(homestr);
    starttrackPacket = hexToBytes(starttrackstr);
    stoptrackPacket = hexToBytes(stoptrackstr);
    down90Packet = hexToBytes(down90str);
    heartbeatPacket = hexToBytes(heartbeatstr);
}

SiyiCamera::~SiyiCamera()
{
    closeCamera();
}


void heartbeat()
{
   
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


    return true;
}

std::vector<uint8_t> SiyiCamera::hexToBytes(const std::string& hex){
    std::vector<uint8_t> bytes;

    for (size_t i = 0; i < hex.length(); i += 2)
    {
	bytes.push_back(
	    static_cast<uint8_t>(
	        std::stoul(hex.substr(i, 2), nullptr, 16)
	    )
	);
    }

    return bytes;
}
void SiyiCamera::sendPacket(const std::vector<uint8_t>& data){
    if (sock_ < 0) return;

    ::send(sock_, data.data(), data.size(), 0);
}
void SiyiCamera::sendHexPacket(const std::string& hex)
{
    if (sock_ < 0) return;

    std::vector<uint8_t> data;
    data.reserve(hex.size() / 2);

    for (size_t i = 0; i < hex.size(); i += 2)
    {
        data.push_back(
            static_cast<uint8_t>(
                std::stoul(hex.substr(i, 2), nullptr, 16)
            )
        );
    }

    ::send(sock_, data.data(), data.size(), 0);
}
void SiyiCamera::turnleft(int speed){
    if (speed<1) sendPacket(leftPackets[0]);
    else if (speed>20) sendPacket(leftPackets[19]);
    else sendPacket(leftPackets[speed-1]);
    
}
void SiyiCamera::turnright(int speed){
    if (speed<1) sendPacket(rightPackets[0]);
    else if (speed>20) sendPacket(rightPackets[19]);
    else sendPacket(rightPackets[speed-1]);
    
}
void SiyiCamera::turnup(int speed){
    if (speed<1) sendPacket(upPackets[0]);
    else if (speed>20) sendPacket(upPackets[19]);
    else sendPacket(upPackets[speed-1]);
    
}
void SiyiCamera::turndown(int speed){
    if (speed<1) sendPacket(downPackets[0]);
    else if (speed>20) sendPacket(downPackets[19]);
    else sendPacket(downPackets[speed-1]);
    
}
void SiyiCamera::zoom(int multiple){
    if (multiple<1) sendPacket(zoomPackets[0]);
    else if (multiple>36) sendPacket(zoomPackets[35]);
    else sendPacket(zoomPackets[multiple-1]);  
    
}


void SiyiCamera::stop(){
    sendPacket(stopPacket);
    
}

void SiyiCamera::down90(){
    sendPacket(down90Packet);
    
}
void SiyiCamera::home(){
    sendPacket(homePacket);
    
}

void SiyiCamera::starttrack(){
    sendPacket(starttrackPacket);
    
}
void SiyiCamera::stoptrack(){
    sendPacket(stoptrackPacket);
    
}


void SiyiCamera::closeCamera()
{
   

    if (sock_ > 0)
        close(sock_);

    std::cout << "Disconnected\n";
}
