#include <gst/gst.h>
#include <iostream>
#include "audioplayer.h"
int main(int argc, char **argv){
	
    	AudioPlayer audioPlayer;
    	audioPlayer.init();
    	if (argc=2){
    		audioPlayer.play(argv[1]);
    		}
    	else std::cout << "please input a source media" << std::endl;
  	return 0;  	
  	
}
