#include <iostream>
#include <opencv2/core.hpp>    // The basic OpenCV structures (Mat)
#include <opencv2/imgcodecs.hpp> // For imread() and imwrite()
#include <opencv2/highgui.hpp>   // For imshow(), 
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "image_functions.h"
#include "video_functions.h"
#include "interactive_image.h"
#include "interactive_video.h"
#include "app_tools.h"



int main() {
 
    /*cv::Mat object_img = read_img("FPV.png");
    cv::Mat scene_img = read_img("FPV.jpg");
    
    cv::resize(scene_img, scene_img, cv::Size((int)scene_img.cols/4,(int)scene_img.rows/4));
    cv::Mat image_matched = image_matching(object_img, scene_img, 1000);
    save_img( "matched_1.jpg",image_matched);
    
    cv::Mat edges = canny_detection(object_img);
    save_img("edges.jpg", edges);
    */
    const std::string file_path = video_path + "test_video.mp4";
    interactive_video(file_path);
    //video_color_detection(file_path);
    //imgInfo(img);
    //interactive_image(&scene_img);
   
    int k = cv::waitKey(0); 

    return 0;
}

