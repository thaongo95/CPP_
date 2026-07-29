#pragma once

#include <string>
#include <vector>
#include <thread>
#include <atomic>

class SiyiCamera
{
public:
    SiyiCamera(std::string ip="192.168.144.25", int port=37260);
    ~SiyiCamera();

    bool connectCamera();
    void closeCamera();

    void sendCommand(uint8_t cmdId, const std::vector<uint8_t>& data = {});
    void formatSD();

private:
    uint16_t crc16(const std::vector<uint8_t>& data);
    std::vector<uint8_t> buildPacket(uint8_t cmdId, const std::vector<uint8_t>& data);

    void heartbeatLoop();

private:
    std::string ip_;
    int port_;
    int sock_;

    std::atomic<bool> running_;
    std::thread heartbeatThread_;

    uint16_t seq_;
};
