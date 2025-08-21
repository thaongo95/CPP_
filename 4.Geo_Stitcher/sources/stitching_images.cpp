#include "stitching_images.h"
#include <chrono>
#include <iostream>

using namespace std;
cv::Mat stitching_images(const std::vector<cv::Mat>& images){
	
   	
	cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(cv::Stitcher::SCANS);
	 
	cv::Mat pano;
	cv::Stitcher::Status status = stitcher->stitch(images, pano);
	
	if (status != cv::Stitcher::OK){
		std::cerr << "ERROR during stitching: " << int(status) << "\n";
	}
	
	return pano;
}

cv::Mat stitching_2(const cv::Mat& image1, const cv::Mat& image2){
	cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(cv::Stitcher::SCANS);
	cv::Mat pano;
	cv::Stitcher::Status status = stitcher->stitch(std::vector<cv::Mat>({image1, image2}), pano);
	if (status != cv::Stitcher::OK){
		std::cerr << "ERROR during stitching: " << int(status) << "\n";
	}
	return pano;
}
