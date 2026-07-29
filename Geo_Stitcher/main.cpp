#include <opencv2/opencv.hpp>
#include <iostream>
#include "stitching_images.h"
#include "utils.h"
#include <utility>
#include <algorithm>

const std::string images_path = "assets/images/";
const std::string csv_path = "assets/image_gps_output.csv";

int main(){
	//std::vector<std::string> filenames = getImagesInFolder(images_path);
	
	std::vector<ImageData> images_data = parseCSV(csv_path);
	std::vector<std::string> filenames;
	for (auto image_data:images_data){
		filenames.push_back(image_data.name);
	}
	for (auto filename:filenames){
		std::cout << filename << "\n" ;
	}
	
        
	std::vector<cv::Mat> images1, images2, images3, images4;
	for (size_t i=0;i<10;i++){
		cv::Mat image = cv::imread(images_path+filenames[i]);
		cv::resize(image, image, cv::Size(1920, 1080), cv::INTER_LINEAR);
		images1.push_back(image);
	}
	cv::Mat result1 = stitching_images(images1);
	cv::imwrite("Stitched_Image_1.jpg", result1);
	std::cout << "Batch 1 finished" << std::endl;
	for (size_t i=10;i<20;i++){
		cv::Mat image = cv::imread(images_path+filenames[i]);
		cv::resize(image, image, cv::Size(1920, 1080), cv::INTER_LINEAR);
		images2.push_back(image);
	}
	cv::Mat result2 = stitching_images(images2);
	cv::imwrite("Stitched_Image_2.jpg", result2);
	std::cout << "Batch 2 finished" << std::endl;
	for (size_t i=20;i<30;i++){
		cv::Mat image = cv::imread(images_path+filenames[i]);
		cv::resize(image, image, cv::Size(1920, 1080), cv::INTER_LINEAR);
		images3.push_back(image);
	}
	cv::Mat result3 = stitching_images(images3);
	cv::imwrite("Stitched_Image_3.jpg", result3);
	std::cout << "Batch 3 finished" << std::endl;
	for (size_t i=30;i<40;i++){
		cv::Mat image = cv::imread(images_path+filenames[i]);
		cv::resize(image, image, cv::Size(1920, 1080), cv::INTER_LINEAR);
		images4.push_back(image);
	}
	cv::Mat result4 = stitching_images(images4);
	cv::imwrite("Stitched_Image_4.jpg", result4);
	std::cout << "Batch 4 finished" << std::endl;
	
	std::vector<cv::Mat> images = {result1, result2, result3, result4};
	cv::Mat result = stitching_images(images);
	cv::imwrite("Stitched_Image_.jpg", result);
	
	cv::resize(result, result, cv::Size(1280, 720), cv::INTER_LINEAR);
	cv::imshow("IMAGE", result);
	cv::waitKey(0);
	cv::destroyAllWindows();
	
	
	
	return 0;
}
