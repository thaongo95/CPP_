#include <iostream>
#include "audioplayer.h"
int main(int   argc,   char **argv) 
{
    AudioPlayer player;
    player.init();
    if (argc > 1) {
        player.play(argv[1]);
    } else {
        std::cerr << "Please provide an audio file path as an argument." << std::endl;
        return -1;  }
    return 0;


}
