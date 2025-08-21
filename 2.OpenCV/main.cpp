#include <iostream>
#include <opencv2/core.hpp>    // The basic OpenCV structures (Mat)
#include <opencv2/imgcodecs.hpp> // For imread() and imwrite()
#include <opencv2/highgui.hpp>   // For imshow(), 
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>

#include "image_functions.h"
#include "video_functions.h"
#include "interactive_image.h"
#include "interactive_video.h"
#include "app_tools.h"
#include "document_scan.h"



int main(int argc,char* argv[]) {
 
    /*cv::Mat object_img = read_img("FPV.png");
    cv::Mat scene_img = read_img("FPV.jpg");
    
    cv::resize(scene_img, scene_img, cv::Size((int)scene_img.cols/4,(int)scene_img.rows/4));
    cv::Mat image_matched = image_matching(object_img, scene_img, 1000);
    save_img( "matched_1.jpg",image_matched);
    
    cv::Mat edges = canny_detection(object_img);
    save_img("edges.jpg", edges);*/
    
    const std::string file_path = video_path + "test_video.mp4";
    //interactive_video(file_path);
    color_detection(file_path);
    
    //imgInfo(img);
    //interactive_image(&scene_img);
    
    /*
    const Color color_ = Color::BLACK;
    cv::Mat object_img = read_img("cards.jpg");
    cv::Mat image = color_detection(object_img, 500, color_);
    save_img("Color_detection.jpg", image);
    cv::imshow("Color detect", image);*/
    
    //cv::Mat object_img = read_img("map2d.png");
    
    //cv::Mat edges = canny_detection(object_img);
    //object_img = edge_detection(object_img, 50);
    //cv::imshow("Edge detection", object_img);
    //cv::imshow("edge detection", edges);
    
    // document scan
    /*cv::Mat doc_img = read_img("paper.jpg");
    imgInfo(doc_img);
    cv::Mat result = get_document_scan(doc_img);
    cv::imshow("Document Scan", result);*/
    
    /*cv::Mat object_img = read_img("FPV.png");
    cv::Mat scene_img = read_img("anh2.jpg");
  
    cv::resize(scene_img, scene_img, cv::Size(1280, 720), cv::INTER_LINEAR);
    cv::resize(object_img, object_img, cv::Size(1280, 720), cv::INTER_LINEAR);
  
    cv::Mat result = image_add(object_img, scene_img, 0.5);
    //cv::addWeighted(object_img, 0.5, scene_img, 0.5, 0.0, result);
    
    cv::Mat image_drawed = draw_shape(result);
    cv::imshow("Image" , image_drawed);
    //result = image_change(result, 0.5, 0);
    cv::Mat linear_cvt, gamma_cvt;
    result.convertTo(linear_cvt, -1, 1.5, 0);
    cv::imshow("Image2" , linear_cvt);
    gamma_cvt = gammaCorrection(result, 2.5);
    cv::imshow("Image3" , gamma_cvt);
    int k = cv::waitKey(0);*/
    
    /*
    cv::Mat img = read_img("cards.jpg");
    return zoom(img);
    */
    
    /*
    cv::Mat img = read_img("cards.jpg");
    threshold_img(&img);
    */
    
    
    cv::waitKey(0);
    return 0;
    
    
}

