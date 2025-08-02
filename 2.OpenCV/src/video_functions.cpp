#include "video_functions.h"
#include "image_functions.h"
#include <sstream>
#include <chrono>

void video_color_detection(const std::string& video_path){
	cv::VideoCapture cap(video_path);
	if (!cap.isOpened()){
		std::cerr << "Error: Could not read video" << std::endl;
		return;
	}
	const std::string windowName = "Video color capture";
	//cv::namedWindow(windowName);
	int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
	int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(cv::CAP_PROP_FPS);
	
	
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
		
		frame = canny_detection(frame);
		
		auto end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end_time - start_time;
		double measured_fps = frame_count/elapsed.count();
		
		std::stringstream ss;
		ss << "Fixed FPS: " << fps << " | Real FPS: " << measured_fps;
		std::string fps_str = ss.str();
		
		cv::putText(frame, fps_str, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255), 2);  
		cv::imshow(windowName,  frame);
		if (cv::waitKey(30) == 'q'){break;}
		
	}
	cap.release();
	cv::destroyAllWindows();
}
