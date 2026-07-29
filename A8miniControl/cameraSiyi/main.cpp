#include "siyi_camera.h"
#include <unistd.h>

int main()
{
    SiyiCamera cam;

    if (!cam.connectCamera())
        return 0;

    sleep(2);

    cam.formatSD();

    sleep(10);

    cam.closeCamera();

    return 0;
}
