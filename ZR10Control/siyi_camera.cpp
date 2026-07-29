#include "siyi_camera.h"

#include <iostream>
#include <cstring>
#include <iomanip>
#include <chrono>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

// Static CRC16 CCITT (0x1021) lookup table from your source
static const uint16_t crc16Table[256]= {
    0x0,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0xa50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0xc60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0xe70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0xa1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x2b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x8e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0xaf1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0xcc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0xed1,0x1ef0
};

SiyiCamera::SiyiCamera()
    : m_socket(-1),
      m_running(false),
      m_sequence(1)
{
}

SiyiCamera::~SiyiCamera()
{
    stop();
    disconnect();
}

bool SiyiCamera::connectToCamera(const std::string& ip, uint16_t port)
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        std::cerr << "socket() failed\n";
        return false;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        std::cerr << "Invalid IP Address\n";
        return false;
    }

    if (connect(m_socket, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "TCP Connection failed\n";
        return false;
    }

    std::cout << "Connected to SIYI Box.\n";
    return true;
}

void SiyiCamera::disconnect()
{
    if (m_socket >= 0) {
        close(m_socket);
        m_socket = -1;
    }
}

bool SiyiCamera::isConnected() const
{
    return m_socket >= 0;
}

void SiyiCamera::start()
{
    if (m_running) return;
    m_running = true;

    // Start network receive loop thread
    m_receiveThread = std::thread(&SiyiCamera::receiveLoop, this);
    
    // Start automated background system heartbeat thread
    m_heartbeatThread = std::thread(&SiyiCamera::heartbeatLoop, this);
}

void SiyiCamera::stop()
{
    m_running = false;

    if (m_receiveThread.joinable())
        m_receiveThread.join();

    if (m_heartbeatThread.joinable())
        m_heartbeatThread.join();
}

bool SiyiCamera::sendAll(const void* buffer, size_t length)
{
    if (m_socket < 0) return false;
    const uint8_t* ptr = static_cast<const uint8_t*>(buffer);

    while (length > 0) {
        ssize_t sent = send(m_socket, ptr, length, 0);
        if (sent <= 0) return false;
        ptr += sent;
        length -= sent;
    }
    return true;
}

bool SiyiCamera::recvAll(void* buffer, size_t length)
{
    if (m_socket < 0) return false;
    uint8_t* ptr = static_cast<uint8_t*>(buffer);

    while (length > 0) {
        ssize_t received = recv(m_socket, ptr, length, 0);
        if (received <= 0) return false;
        ptr += received;
        length -= received;
    }
    return true;
}

uint16_t SiyiCamera::nextSequence()
{
    return m_sequence++;
}

void SiyiCamera::printHex(const std::vector<uint8_t>& data) const
{
    std::cout << std::hex << std::setfill('0');
    for (auto b : data) {
        std::cout << std::setw(2) << static_cast<int>(b) << " ";
    }
    std::cout << std::dec << std::endl;
}

uint16_t SiyiCamera::CRC16(const uint8_t* data, uint32_t len, uint16_t crcInit)
{
    uint16_t crc = crcInit;
    uint16_t oldcrc16;
    uint8_t temp;

    while (len--) {
        temp = (crc >> 8) & 0xFF;
        oldcrc16 = crc16Table[*data ^ temp];
        crc = (crc << 8) ^ oldcrc16;
        data++;
    }
    return crc;
}

std::vector<uint8_t> SiyiCamera::buildPacket(uint8_t cmd, const std::vector<uint8_t>& data, uint8_t ctrl)
{
    std::vector<uint8_t> packet;
    
    // 1. STX (Magic Preamble Header Start Tokens)
    packet.push_back(0x55);
    packet.push_back(0x66);

    // 2. CTRL (Control Byte)
    packet.push_back(ctrl);

    // 3. DATA LENGTH (Little-Endian)
    uint16_t len = static_cast<uint16_t>(data.size());
    packet.push_back(len & 0xFF);
    packet.push_back((len >> 8) & 0xFF);

    // 4. Sequence Number (Little-Endian)
    uint16_t seq = nextSequence();
    packet.push_back(seq & 0xFF);
    packet.push_back((seq >> 8) & 0xFF);

    // 5. Command ID
    packet.push_back(cmd);

    // 6. Data Payload
    if (!data.empty()) {
        packet.insert(packet.end(), data.begin(), data.end());
    }

    // 7. CRC16 Checksum over entire buffer (excluding CRC slots)
    uint16_t crc = CRC16(packet.data(), packet.size());
    packet.push_back(crc & 0xFF);
    packet.push_back((crc >> 8) & 0xFF);

    return packet;
}

bool SiyiCamera::parsePacket(const std::vector<uint8_t>& raw, Packet& packet)
{
    // Minimal valid packet payload envelope length is 10 bytes:
    // STX(2) + CTRL(1) + LEN(2) + SEQ(2) + CMD(1) + CRC(2) = 10
    if (raw.size() < 10) return false;

    // Validate the Start Token bytes match
    if (raw[0] != 0x55 || raw[1] != 0x66) {
        return false; 
    }

    if (!verifyCRC(raw)) {
        std::cerr << "CRC Error on Recv Packet\n";
        return false;
    }

    packet.ctrl = raw[2];
    uint16_t len = raw[3] | (raw[4] << 8);
    packet.seq = raw[5] | (raw[6] << 8);
    packet.cmd = raw[7];

    packet.data.assign(raw.begin() + 8, raw.begin() + 8 + len);
    return true;
}

bool SiyiCamera::receivePacket(Packet& packet)
{
    uint8_t stx[2] = {0, 0};
    
    // 1. Sync loop: Advance the TCP stream until we hit a valid 0x55 0x66 header pattern
    while (m_running) {
        if (!recvAll(&stx[0], 1)) return false;
        if (stx[0] == 0x55) {
            if (!recvAll(&stx[1], 1)) return false;
            if (stx[1] == 0x66) {
                break; // Synced up successfully with header preamble tokens!
            }
        }
    }

    // 2. Read the remaining fixed portion of the header: CTRL (1), LEN (2), SEQ (2), CMD (1) = 6 bytes
    uint8_t headerFields[6];
    if (!recvAll(headerFields, 6)) return false;

    uint8_t ctrl = headerFields[0];
    uint16_t len = headerFields[1] | (headerFields[2] << 8);
    uint16_t seq = headerFields[3] | (headerFields[4] << 8);
    uint8_t cmd  = headerFields[5];

    // 3. Assemble our validation container array
    std::vector<uint8_t> raw;
    raw.push_back(0x55);
    raw.push_back(0x66);
    raw.insert(raw.end(), headerFields, headerFields + 6);

    // 4. Read the variable Data Payload component if specified
    if (len > 0) {
        std::vector<uint8_t> payload(len);
        if (!recvAll(payload.data(), len)) return false;
        raw.insert(raw.end(), payload.begin(), payload.end());
    }

    // 5. Pull down the trailing CRC validation checksum block (2 bytes)
    uint8_t crc[2];
    if (!recvAll(crc, 2)) return false;
    raw.push_back(crc[0]);
    raw.push_back(crc[1]);

    // 6. Send off to structural packet conversion engine
    return parsePacket(raw, packet);
}

bool SiyiCamera::sendPacket(uint8_t cmd, const std::vector<uint8_t>& data, uint8_t ctrl)
{
    std::lock_guard<std::mutex> lock(m_sendMutex);
    auto packet = buildPacket(cmd, data, ctrl);
    
    // Comment out TX debug if log lines are too chatty
    // std::cout << "TX : "; printHex(packet); 
    
    return sendAll(packet.data(), packet.size());
}

bool SiyiCamera::verifyCRC(const std::vector<uint8_t>& raw)
{
    if (raw.size() < 8) return false;

    uint16_t crcRecv = raw[raw.size() - 2] | (raw[raw.size() - 1] << 8);
    uint16_t crcCalc = CRC16(raw.data(), raw.size() - 2);

    return crcRecv == crcCalc;
}



void SiyiCamera::receiveLoop()
{
    while (m_running) {
        Packet packet;
        if (!receivePacket(packet)) {
            std::cerr << "Connection closed or receive link error.\n";
            m_running = false;
            break;
        }
        handlePacket(packet);
    }
}

void SiyiCamera::heartbeatLoop()
{
    while (m_running) {
        sendHeartbeat();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// ======================== API CONTROLS IMPLEMENTATION ========================

bool SiyiCamera::sendHeartbeat() {
    return sendPacket(0x00, {}, 0x01); // 0x00 Heartbeat (ctrl=1 requires ack)
}

bool SiyiCamera::requestVersion() {
    return sendPacket(0x01, {}, 0x01); // 0x01 Read Firm Version
}

bool SiyiCamera::requestAIStatus() {
    return sendPacket(0x03, {}, 0x01); // 0x03 Read AI Mode Status
}

bool SiyiCamera::setAIStatus(bool enable) {
    std::vector<uint8_t> data = { static_cast<uint8_t>(enable ? 1 : 0) };
    return sendPacket(0x04, data, 0x01); // 0x04 Write AI Mode Status
}

bool SiyiCamera::requestTrackingStatus() {
    return sendPacket(0x05, {}, 0x01); // 0x05 Read Tracking Mode Status
}
// 0x08 Get AI Module Tracking Coordinate Information Stream Status
bool SiyiCamera::requestAIStreamStatus() {
    return sendPacket(0x08, {}, 0x01); // ctrl=0x01 requires an ACK response
}

// 0x09 Set AI Module Tracking Coordinate Information Stream Status
// track_action: 1 = Open/Enable Output, 0 = Close/Disable Output
bool SiyiCamera::setAIStreamStatus(uint8_t track_action) {
    std::vector<uint8_t> data = { track_action };
    return sendPacket(0x09, data, 0x01); // ctrl=0x01 requires an ACK response
}
bool SiyiCamera::setAITargetTracking(uint8_t action, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    std::vector<uint8_t> data(9);
    data[0] = action; // 1: Track target, 0: Cancel target tracking
    
    // Store variables explicitly as Little-Endian
    data[1] = x1 & 0xFF; data[2] = (x1 >> 8) & 0xFF;
    data[3] = y1 & 0xFF; data[4] = (y1 >> 8) & 0xFF;
    data[5] = x2 & 0xFF; data[6] = (x2 >> 8) & 0xFF;
    data[7] = y2 & 0xFF; data[8] = (y2 >> 8) & 0xFF;

    return sendPacket(0x06, data, 0x00); // 0x06 Set AI Trace Config Target
}
bool SiyiCamera::stopTracking() {
    // Action = 0 cancels tracking; coordinates are ignored by the gimbal when action is 0
    return setAITargetTracking(0, 0, 0, 0, 0);
}
bool SiyiCamera::enableRTSP(bool enable) {
    std::vector<uint8_t> data = { static_cast<uint8_t>(enable ? 1 : 0) };
    return sendPacket(0x0B, data, 0x01); // 0x0B Open / Close stream
}

// ======================== PROTOCOL PACKET PARSING ========================

void SiyiCamera::handlePacket(const Packet& packet)
{
    std::cout << "\n----------------------------------------\n";
    std::cout << "[RX DATA ENVELOPE] Command: 0x" << std::hex << std::setfill('0') << std::setw(2) << (int)packet.cmd 
              << " | Seq No: " << std::dec << packet.seq 
              << " | Payload Size: " << packet.data.size() << " bytes\n";

    switch (packet.cmd) {
        case 0x00:
            std::cout << ">>> [HEARTBEAT ACK] Keep-alive confirmation accepted.\n";
            break;
            
        case 0x01:
            handleVersion(packet);
            break;
            
        case 0x03:
            handleAIStatus(packet);
            break;
            
        case 0x04:
            if (!packet.data.empty()) {
                std::cout << ">>> [AI SET ACK] Write return code: " << (int)packet.data[0];
                if (packet.data[0] == 1) std::cout << " (Success)\n";
                else std::cout << " (Failed/Rejected)\n";
            }
            break;
            
        case 0x05:
            handleTrackingStatus(packet);
            break;
            
        case 0x06:
            if (!packet.data.empty()) {
                std::cout << ">>> [TRACKING TARGET ACK] Lock configuration response code: " << (int)packet.data[0];
                if (packet.data[0] == 1) std::cout << " (Tracking target locked successfully)\n";
                else std::cout << " (Failed to initialize bounding box tracking)\n";
            }
            break;
            
        case 0x0A:
            handleTrackingCoordinates(packet);
            break;

        case 0x0B:
            if (!packet.data.empty()) {
                std::cout << ">>> [RTSP CONFIG ACK] Video pipeline command execution state: " << (int)packet.data[0] << "\n";
            }
            break;
        case 0x08:
            handleAIStreamStatus(packet);
            break;
            
        case 0x09:
            if (!packet.data.empty()) {
                uint8_t sta = packet.data[0];
                std::cout << ">>> [AI STREAM SET ACK (0x09)] Gimbal Reported State: " << (int)sta;
                if (sta == 1) {
                    std::cout << " (\033[1;32mStream Output Opened / Active\033[0m)\n";
                } else if (sta == 0) {
                    std::cout << " (\033[1;33mStream Output Closed / Inactive\033[0m)\n";
                } else {
                    std::cout << " (Unexpected Error / State)\n";
                }
            }
            break; 
        default:
            std::cout << ">>> [UNKNOWN CMD CORRELATION] Raw payload bytes: ";
            printHex(packet.data);
            break;
    }
    std::cout << "----------------------------------------\n";
}

void SiyiCamera::handleVersion(const Packet& packet)
{
    if (packet.data.size() >= 4) {
        // According to the document sample: fields map to specific major/minor/revision offsets
        std::cout << ">>> [FIRMWARE DATA] Version: v" 
                  << (int)packet.data[2] << "." 
                  << (int)packet.data[1] << "." 
                  << (int)packet.data[0] 
                  << " | Target Build Flags: 0x" << std::hex << (int)packet.data[3] << std::dec << "\n";
    } else {
        std::cout << ">>> [FIRMWARE DATA] Malformed data array size.\n";
    }
}

void SiyiCamera::handleAIStatus(const Packet& packet)
{
    if (packet.data.empty()) return;
    uint8_t status = packet.data[0];
    std::cout << ">>> [AI ENGINE STATE] Current Mode: " 
              << (status == 1 ? "\033[1;32mON / ACTIVE\033[0m" : "\033[1;31mOFF / DISABLED\033[0m") 
              << " (Raw code: " << (int)status << ")\n";
}

void SiyiCamera::handleTrackingStatus(const Packet& packet)
{
    if (packet.data.empty()) return;
    uint8_t tracking = packet.data[0];
    std::cout << ">>> [TRACKING CONFIG STATE] Engine lock: " 
              << (tracking == 1 ? "\033[1;36mENGAGED & TRACKING\033[0m" : "\033[1;33mIDLE / NO TARGET STABILIZED\033[0m") 
              << "\n";
}
void SiyiCamera::handleAIStreamStatus(const Packet& packet)
{
    if (packet.data.empty()) {
        std::cout << ">>> [AI STREAM STATUS (0x08)] Received empty payload.\n";
        return;
    }

    uint8_t sta = packet.data[0];
    std::string status_str = "Unknown Status";

    switch (sta) {
        case 0: status_str = "Not Opened / Closed"; break;
        case 1: status_str = "\033[1;32mActively Outputting Coordinate Stream\033[0m"; break;
        case 2: status_str = "AI Identification Engine Not Opened"; break;
        case 3: status_str = "AI Target Tracking Engine Not Opened"; break;
        default: status_str = "RFU / Reserved Code"; break;
    }

    std::cout << ">>> [AI STREAM STATUS (0x08)] Current Link State: " << status_str 
              << " (Raw sta: " << (int)sta << ")\n";
}
void SiyiCamera::handleTrackingCoordinates(const Packet& packet)
{
    if (packet.data.size() < 10) {
        std::cout << ">>> [AI TARGET BROADCAST] Truncated telemetry packet received.\n";
        return;
    }

    // Little-Endian unpacking of the 0x0A auto-broadcast sequence
    uint16_t pos_x  = packet.data[0] | (packet.data[1] << 8);
    uint16_t pos_y  = packet.data[2] | (packet.data[3] << 8);
    uint16_t width  = packet.data[4] | (packet.data[5] << 8);
    uint16_t height = packet.data[6] | (packet.data[7] << 8);
    uint8_t  target = packet.data[8]; // 0: Person, 1: Car, 2: Bus, 3: Truck, 255: Any Object
    uint8_t  status = packet.data[9]; // Tracking operational statuses

    std::string class_type = "Unknown";
    if (target == 0) class_type = "Person";
    else if (target == 1) class_type = "Car";
    else if (target == 2) class_type = "Bus";
    else if (target == 3) class_type = "Truck";
    else if (target == 255) class_type = "Generic/Any Object";

    std::string track_str = "Unknown";
    if (status == 0) track_str = "Normal Tracking (AI)";
    else if (status == 1) track_str = "Intermittent Loss (Tracking)";
    else if (status == 2) track_str = "Lost Target";
    else if (status == 3) track_str = "Cancelled by User";
    else if (status == 4) track_str = "Normal Tracking (Generic)";

    std::cout << "\n>>> \033[1;35m[AI TRACKING MATRIX TELEMETRY (0x0A)]\033[0m\n"
              << "    Target Center Offset: (" << pos_x << ", " << pos_y << ")\n"
              << "    Bounding Dimensions : [" << width << " x " << height << "]\n"
              << "    Identified Class    : " << class_type << " (ID: " << (int)target << ")\n"
              << "    Engine Lock State   : " << track_str << "\n"
              << "----------------------------------------\n";
}
