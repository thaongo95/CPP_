#ifndef STITCHING_IMAGES_H
#define STITCHING_IMAGES_H

#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include <vector>

cv::Mat stitching_images(const std::vector<cv::Mat>& images);
cv::Mat stitching_2(const cv::Mat& image1, const cv::Mat& image2);


#endif
