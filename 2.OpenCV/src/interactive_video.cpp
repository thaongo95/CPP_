#include "interactive_video.h"
#include <vector>

int h_min = 0, s_min = 0, v_min =0;
int h_max = 179, s_max = 255, v_max = 255;
const std::string windowName = "Color Detector";
const std::string trackbarName = "Trackbars";

void on_trackbar(int, void*){}

void createTrackbars(){
	cv::namedWindow(trackbarName, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("H_MIN", trackbarName, &h_min, 179, on_trackbar);
	cv::createTrackbar("H_MAX", trackbarName, &h_max, 179, on_trackbar);
	cv::createTrackbar("S_MAX", trackbarName, &s_max, 255, on_trackbar);
	cv::createTrackbar("S_MIN", trackbarName, &s_min, 255, on_trackbar);
	cv::createTrackbar("V_MAX", trackbarName, &v_max, 255, on_trackbar);
	cv::createTrackbar("V_MIN", trackbarName, &v_min, 255, on_trackbar);
}
void interactive_video(const std::string& source){

	cv::VideoCapture cap(source);
	if (!cap.isOpened()) {
		std::cerr << "Error: Video capture fail" << std::endl;
	}
	cv::Mat frame, hsv_frame, mask;
	createTrackbars();
	cv::setTrackbarPos("H_MIN", trackbarName, 0);
	cv::setTrackbarPos("H_MAX", trackbarName, 25);
	cv::setTrackbarPos("S_MIN", trackbarName, 100);
	cv::setTrackbarPos("S_MAX", trackbarName, 255);
	cv::setTrackbarPos("V_MIN", trackbarName, 100);
	cv::setTrackbarPos("V_MAX", trackbarName, 255);
	while (true){
		bool success = cap.read(frame);
		if (!success) {
			std::cerr << "Error: Frame reading fail" << std::endl;
			break;
		}
		
		cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);
		
		cv::Scalar lower_bound(h_min, s_min, v_min);
		cv::Scalar upper_bound(h_max, s_max, v_max);
		
		cv::inRange(hsv_frame, lower_bound, upper_bound, mask);
		
		cv::erode(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
		
		cv::dilate(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
		
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		
		for (size_t i=0; i< contours.size(); i++){
			double area = cv::contourArea(contours[i]);
			if (area > 100){
				// Get the bounding rectangle for the largest contour
		    		cv::Rect bounding_rect = cv::boundingRect(contours[i]);
		    		// Draw the rectangle on the original frame
		    		cv::rectangle(frame, bounding_rect, cv::Scalar(0, 255, 0), 2);
			}
		}
		
 		cv::imshow("Original Frame", frame);
		cv::imshow("Mask", mask);
		if (cv::waitKey(20)=='q') break;
	}
	cap.release();
	cv::destroyAllWindows();
}
