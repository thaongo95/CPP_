#pragma once
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdint>

struct Packet {
    uint8_t ctrl;
    uint16_t seq;
    uint8_t cmd;
    std::vector<uint8_t> data;
};

class SiyiCamera {
public:
    SiyiCamera();
    ~SiyiCamera();

    bool connectToCamera(const std::string& ip, uint16_t port);
    void disconnect();
    bool isConnected() const;

    void start();
    void stop();

    // Controls
    bool sendHeartbeat();
    bool requestVersion();
    bool requestAIStatus();
    bool setAIStatus(bool enable);
    bool requestTrackingStatus();
    bool requestAIStreamStatus();                          
    bool setAIStreamStatus(uint8_t track_action);
    bool setAITargetTracking(uint8_t action, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    bool enableRTSP(bool enable);
    bool stopTracking();

private:
    int m_socket;
    bool m_running;
    uint16_t m_sequence;
    
    std::thread m_receiveThread;
    std::thread m_heartbeatThread;
    std::mutex m_sendMutex;

    void receiveLoop();
    void heartbeatLoop();
    
    bool sendAll(const void* buffer, size_t length);
    bool recvAll(void* buffer, size_t length);
    uint16_t nextSequence();
    void printHex(const std::vector<uint8_t>& data) const;

    uint16_t CRC16(const uint8_t* data, uint32_t len, uint16_t crcInit = 0x0000);
    std::vector<uint8_t> buildPacket(uint8_t cmd, const std::vector<uint8_t>& data, uint8_t ctrl);
    bool sendPacket(uint8_t cmd, const std::vector<uint8_t>& data = {}, uint8_t ctrl = 0x01);
    
    bool receivePacket(Packet& packet);
    bool parsePacket(const std::vector<uint8_t>& raw, Packet& packet);
    bool verifyCRC(const std::vector<uint8_t>& raw);

    void handlePacket(const Packet& packet);
    void handleVersion(const Packet& packet);
    void handleAIStatus(const Packet& packet);
    void handleTrackingStatus(const Packet& packet);
    void handleAIStreamStatus(const Packet& packet);
    void handleTrackingCoordinates(const Packet& packet);
};
