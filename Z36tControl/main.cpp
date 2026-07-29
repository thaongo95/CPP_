#include "siyi_camera.h"
#include <unistd.h>
#include <iostream>
#include <sstream>

int main()
{
    SiyiCamera cam;

    if (!cam.connectCamera())
        return 0;

    std::string line;

    std::cout << "Enter commands:\n";
    std::cout << "turnleft N | turnright N | turnup N | turndown N | zoom N | down90 | stop | home | quit\n";

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::stringstream ss(line);
        std::string cmd;
        int value = 0;

        ss >> cmd;

        if (cmd == "quit")
            break;

        if (cmd == "stop")
        {
            cam.stop();
        }
        else if (cmd == "home")
        {
            cam.home();
        }
        else if (cmd == "down90")
        {
            cam.down90();
        }
        else if (cmd == "starttrack")
        {
            cam.starttrack();
        }
        else if (cmd == "stoptrack")
        {
            cam.stoptrack();
        }
        else
        {
            ss >> value;

            if (cmd == "turnleft")
                cam.turnleft(value);
            else if (cmd == "turnright")
                cam.turnright(value);
            else if (cmd == "turnup")
                cam.turnup(value);
            else if (cmd == "turndown")
                cam.turndown(value);
            else if (cmd == "zoom")
                cam.zoom(value);
            else
                std::cout << "Unknown command\n";
        }
    }

    std::cout << "Exiting...\n";
    return 0;
}
