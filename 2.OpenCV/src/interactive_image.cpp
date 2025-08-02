#include "interactive_image.h"
#include <string>
#include <sstream>
#include <vector>
void onMouse(int event, int x, int y, int flags, void* userdata){
	if (event != cv::EVENT_MOUSEMOVE){return;}
	cv::Mat* imagePtr = static_cast<cv::Mat*>(userdata);
	cv::Mat image = *imagePtr;
	if (x < 0 || x >= image.cols || y < 0 || y >= image.rows) {
		// The mouse cursor is outside the image boundaries.
		// This can sometimes happen for a single frame when moving the mouse quickly.
		// Just ignore this event.
		return;
	}

	cv::Mat displayImage;
	image.copyTo(displayImage);

	cv::Vec3b pixel = image.at<cv::Vec3b>(y,x);
	int blue = pixel[0];
	int green = pixel[1];
	int red = pixel[2];
	std::stringstream ss;
	ss << "Pos: (" << x << ", " << y << ") | BGR: (" << blue << ", " << green << ", " << red << ")";
	std::string infoText = ss.str();
	cv::circle(displayImage, cv::Point(x,y), 5, cv::Scalar(255, 0, 0), -1);
	
	//Draw info on the image
	cv::Size textSize = cv::getTextSize(infoText, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, nullptr);
	cv::Rect textBackground(cv::Point(x+5,y+5), cv::Size(textSize.width +10, textSize.height +10));
	cv::rectangle(displayImage, textBackground, cv::Scalar(255-blue,255-green,255-red), cv::FILLED);
	cv::putText(displayImage, infoText, cv::Point(x+10, y+20),cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(blue,green,red), 1);
	const std::string windowName = "Image Inspector";
	cv::imshow(windowName, displayImage);
}
void interactive_image(cv::Mat* img){
	const std::string windowName = "Image Inspector";
	cv::namedWindow(windowName);

	cv::setMouseCallback(windowName, onMouse, img);
	cv::imshow(windowName, *img);

}
