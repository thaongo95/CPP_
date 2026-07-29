#include "siyi_camera.h"
#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <thread>

void printMenu() {
    std::cout << "\n========== SIYI AI Box Test Menu ==========\n"
              << "1. Request Firmware Version (0x01)\n"
              << "2. Request AI Recognition Status (0x03)\n"
              << "3. Turn AI Recognition ON (0x04)\n"
              << "4. Turn AI Recognition OFF (0x04)\n"
              << "5. Request Target Tracking Status (0x05)\n"
              << "6. Set AI Tracking Target Box (0x06)\n"
              << "7. Cancel Target Tracking (0x06)\n"
              << "8. Toggle RTSP Video Stream (0x0B)\n"
              << "9. Request Telemetry Stream Status (0x08)\n"
              << "10. Toggle Telemetry Auto-Broadcast (0x09)\n"
              << "0. Exit\n"
              << "--------------------------------------------\n"
              << "Enter choice: ";
}

int main() {
    // Target IP address and Control Protocol TCP Port
    const std::string camera_ip = "192.168.144.60"; 
    const uint16_t camera_port = 37260; 

    SiyiCamera camera;

    std::cout << "Connecting to camera at " << camera_ip << ":" << camera_port << "..." << std::endl;
    if (!camera.connectToCamera(camera_ip, camera_port)) {
        std::cerr << "CRITICAL: Could not establish TCP connection to SIYI Box." << std::endl;
        return -1;
    }

    // Spin up the background receive loop and the 2-second automated heartbeat thread
    camera.start();
    std::cout << "Background worker threads started successfully.\n";

    int choice = -1;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            std::cout << "Exiting application..." << std::endl;
            break;
        }

        switch (choice) {
            case 1:
                std::cout << "Sending Request for Firmware Version...\n";
                camera.requestVersion();
                break;
            case 2:
                std::cout << "Sending Request for AI Status...\n";
                camera.requestAIStatus();
                break;
            case 3:
                std::cout << "Enabling AI Recognition Mode...\n";
                camera.setAIStatus(true);
                break;
            case 4:
                std::cout << "Disabling AI Recognition Mode...\n";
                camera.setAIStatus(false);
                break;
            case 5:
                std::cout << "Sending Request for Tracking Status...\n";
                camera.requestTrackingStatus();
                break;
            case 6: {
                uint16_t x1, y1, x2, y2;
                std::cout << "Enter tracking target parameters (mapped to a 1280x720 plane):\n";
                std::cout << "Top-Left X1: ";     std::cin >> x1;
                std::cout << "Top-Left Y1: ";     std::cin >> y1;
                std::cout << "Bottom-Right X2: "; std::cin >> x2;
                std::cout << "Bottom-Right Y2: "; std::cin >> y2;
                
                std::cout << "Sending Target Box Tracking configuration...\n";
                camera.setAITargetTracking(1, x1, y1, x2, y2); // Action 1 = Track
                break;
            }
            case 7:
                std::cout << "Sending Cancel Tracking request...\n";
                camera.setAITargetTracking(0, 0, 0, 0, 0); // Action 0 = Cancel/Stop
                break;
            case 8: {
                int toggle;
                std::cout << "Enter 1 to Open Video Stream, 0 to Close Video Stream: ";
                std::cin >> toggle;
                camera.enableRTSP(toggle == 1);
                break;
            }
            case 9:
                std::cout << "Querying Telemetry Stream Status (0x08)...\n";
                camera.requestAIStreamStatus();
                break;
            case 10: {
                int toggle;
                std::cout << "Enter 1 to Start Auto-Broadcast (0x0A stream), 0 to Stop: ";
                std::cin >> toggle;
                std::cout << "Sending Telemetry Auto-Broadcast configuration (0x09)...\n";
                camera.setAIStreamStatus(static_cast<uint8_t>(toggle == 1 ? 1 : 0));
                break;
            }
            default:
                std::cout << "Invalid menu selection. Please try again.\n";
                break;
        }

        // Give the background thread a brief moment to print any arriving incoming ACKs
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    // Clean up connections and threads cleanly on closure
    std::cout << "Stopping background loops..." << std::endl;
    camera.stop();
    camera.disconnect();
    std::cout << "Disconnected securely. Goodbye." << std::endl;

    return 0;
}
