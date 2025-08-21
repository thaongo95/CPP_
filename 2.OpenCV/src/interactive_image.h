#ifndef INTERACTIVE_IMAGE
#define INTERACTIVE_IMAGE
#include <opencv2/opencv.hpp>

void get_mouse_info(cv::Mat* img);

void erosion_dilation(cv::Mat* img);

int zoom(cv::Mat& image);

void threshold_img(cv::Mat* img);

#endif
