#include "video_functions.h"
#include "image_functions.h"
#include <sstream>
#include <chrono>

const std::string windowName = "Video color capture";

int h_low=0, h_high=255, s_low=0, s_high=255, v_low=0, v_high=255;
void on_H_LOW(int, void*){h_low = cv::getTrackbarPos("H_LOW", windowName);}
void on_H_HIGH(int, void*){h_high = cv::getTrackbarPos("H_HIGH", windowName);}
void on_S_LOW(int, void*){s_low = cv::getTrackbarPos("S_LOW", windowName);}
void on_S_HIGH(int, void*){s_high = cv::getTrackbarPos("S_HIGH", windowName);}
void on_V_LOW(int, void*){v_low = cv::getTrackbarPos("V_LOW", windowName);}
void on_V_HIGH(int, void*){v_high = cv::getTrackbarPos("V_HIGH", windowName);}

void hsv_detection(const std::string& video_path){
	cv::VideoCapture cap(video_path);
	if (!cap.isOpened()){
		std::cerr << "Error: Could not read video" << std::endl;
		return;
	}
	cv::namedWindow(windowName);
	int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
	int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(cv::CAP_PROP_FPS);
	cv::createTrackbar("H_LOW", windowName, &h_low, 255, on_H_LOW);
	cv::createTrackbar("H_HIGH", windowName, &h_high, 255, on_H_HIGH);
	cv::createTrackbar("S_LOW", windowName, &s_low, 255, on_S_LOW);
	cv::createTrackbar("S_HIGH", windowName, &s_high, 255, on_S_HIGH);
	cv::createTrackbar("V_LOW", windowName, &v_low, 255, on_V_LOW);
	cv::createTrackbar("V_HIGH", windowName, &v_high, 255, on_V_HIGH);
	auto start_time = std::chrono::high_resolution_clock::now();
	int frame_count =0;
	while(true){
	
		cv::Mat frame;
		bool success = cap.read(frame);
		
		if (!success){
			std::cerr << "Error: Cant not read frame" << std::endl;
			break;
		}
		else frame_count++;
		
		cv::Mat hsv;
		cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV); 
		cv::inRange(frame, cv::Scalar(h_low, s_low, v_low), cv::Scalar(h_high, s_high, v_high), hsv);
		//frame = canny_detection(frame);
		
		auto end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end_time - start_time;
		double measured_fps = frame_count/elapsed.count();
		
		std::stringstream ss;
		ss << "Fixed FPS: " << fps << " | Real FPS: " << measured_fps;
		std::string fps_str = ss.str();
		
		cv::putText(frame, fps_str, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255), 2);  
		cv::imshow(windowName,  hsv);
		if (cv::waitKey(30) == 'q'){break;}
		
	}
	cap.release();
	cv::destroyAllWindows();
}

Color color_= Color::RED;
void onTrackColor(int, void*){
	color_ = static_cast<Color>(cv::getTrackbarPos("COLOR", windowName));
}
void color_detection(const std::string& video_path){
	cv::VideoCapture cap(video_path);
	if (!cap.isOpened()){std::cerr << "Video cannot open" << std::endl;return;}
	cv::namedWindow(windowName);
	cv::createTrackbar("COLOR", windowName, nullptr, 4, onTrackColor);
	while(true){
		cv::Mat frame;
		bool success = cap.read(frame);
		cv::Mat result = color_detection(frame, 500, color_);
		cv::imshow(windowName,  result);
		if (cv::waitKey(30) == 'q'){break;}
	}
	cap.release();
	cv::destroyAllWindows();
}




