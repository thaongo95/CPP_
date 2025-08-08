#include "document_scan.h"
#include "image_functions.h"
#include <vector>

std::vector<cv::Point2f> reorderPoints(const std::vector<cv::Point>& points){
	std::vector<cv::Point2f> ordered(4);
	std::vector<cv::Point2f> pts(points.begin(), points.end());
	std::sort(pts.begin(), pts.end(), [](cv::Point2f a, cv::Point2f b){
		return a.x + a.y < b.x +b.y;
	});
	ordered[0] = pts[0]; //top-left
	ordered[3] = pts[3]; // bottom-right
	std::sort(pts.begin(), pts.end(), [](cv::Point2f a, cv::Point2f b){
		return a.y - a.x < b.y - b.x;
	});
	ordered[1] = pts[0];  //top-right
	ordered[2] = pts[3];  //bottom-left
	return ordered;
}


cv::Mat get_document_scan(const cv::Mat& image){
	// Step 1: Preprocess
	cv::Mat canny = canny_detection(image);
	
	cv::Mat img = image.clone();
	//Step 2: Find contours
	
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(canny, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	
	std::vector<cv::Point> doc_contour;
	double max_area = 0;
	int max_id = 0, count = 0;
	for (const auto& contour: contours){
		double area = cv::contourArea(contour);
		
		std::cout << count << " : " <<  area << std::endl;
		
		if (area>1000){
			std::vector<cv::Point> approx;
			cv::approxPolyDP(contour, approx, 0.02*cv::arcLength(contour, true), true);
			if (approx.size() == 4 && area > max_area){
				doc_contour = approx;
				max_area = area;
				max_id = count;
			}
		}
		count++;
	}
	
	if (doc_contour.empty()){
		std::cout << "No document found. \n";
	}
	cv::drawContours(img, contours, max_id, cv::Scalar(0,255,0), 2);
	//Step 3 Warp perspective
	
	auto ordered = reorderPoints(doc_contour);
	float width =420, height = 596;
	std::vector<cv::Point2f> dst = {{0,0}, {width,0}, {0,height}, {width,height} };
	cv::Mat matrix = cv::getPerspectiveTransform(ordered, dst);
	cv::Mat scanned;
	cv::warpPerspective(image, scanned, matrix, cv::Size(width, height));
	cv::imshow("Scan doc", scanned);
	
	//Step 4 Optional post-processing 
	cv::Mat final_;
	cv::cvtColor(scanned, final_, cv::COLOR_BGR2GRAY);
	cv::adaptiveThreshold(final_, final_, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11,10);
	return final_;
}
