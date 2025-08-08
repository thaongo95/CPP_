#ifndef IMAGE_FUNCTIONS_H
#define IMAGE_FUNCTIONS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <utility>
#include "app_tools.h"

cv::Mat canny_detection(const cv::Mat& image);
cv::Mat edge_detection(const cv::Mat& image, const double& erea_threshold);

//std::pair<std::vector<cv::KeyPoint>, cv::Mat> 
auto orb_detection(const cv::Mat& image,const int& nfeatures);

cv::Mat image_matching(const cv::Mat& object,const cv::Mat& scene,const int& nfeatures);

cv::Mat color_detection(const cv::Mat& object, const double& erea_threshold, const Color& color_);





#endif
