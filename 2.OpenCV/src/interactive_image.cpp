#include "interactive_image.h"
#include <string>
#include <sstream>
#include <vector>

// use for get_mouse_info
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

void get_mouse_info(cv::Mat* img){
	const std::string windowName = "Image Inspector";
	cv::namedWindow(windowName);

	cv::setMouseCallback(windowName, onMouse, img);
	cv::imshow(windowName, *img);

}

void Erosion(int,void* userdata){
	int erosion_type= 0;
	cv::Mat erosion_dst;
	cv::Mat* src = static_cast<cv::Mat*>(userdata);
	int erosion_elem = cv::getTrackbarPos("Element", "Erosion");
	int erosion_size = cv::getTrackbarPos("Kernel", "Erosion");
	if( erosion_elem == 0 ){ erosion_type = cv::MORPH_RECT; }
  	else if( erosion_elem == 1 ){ erosion_type = cv::MORPH_CROSS; }
  	else if( erosion_elem == 2) { erosion_type = cv::MORPH_ELLIPSE; }
  	else if( erosion_elem == 3) { erosion_type = cv::MORPH_ELLIPSE; }
  	
  	/*cv::Mat cv::getStructuringElement(
	    int shape,        // Shape of structuring element
	    cv::Size ksize,   // Size of structuring element
	    cv::Point anchor = Point(-1, -1) // Anchor point (default = center)
	);*/
  	cv::Mat element = cv::getStructuringElement( erosion_type,   
                       cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       cv::Point( -1, -1 ) );
 	cv::erode(*src, erosion_dst, element );
	cv::imshow( "Erosion", erosion_dst );
}
void Dilation(int,void* userdata){
	int dilation_type= 0;
	cv::Mat dilation_dst;
	cv::Mat* src = static_cast<cv::Mat*>(userdata);
	int dilation_elem = cv::getTrackbarPos("Element", "Dilation");
	int dilation_size = cv::getTrackbarPos("Kernel", "Dilation");
	if( dilation_elem == 0 ){ dilation_type = cv::MORPH_RECT; }
  	else if( dilation_elem == 1 ){ dilation_type = cv::MORPH_CROSS; }
  	else if( dilation_elem == 2) { dilation_type = cv::MORPH_ELLIPSE; }
  	else if( dilation_elem == 3) { dilation_type = cv::MORPH_ELLIPSE; }
  	cv::Mat element = cv::getStructuringElement( dilation_type,
                       cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       cv::Point( dilation_size, dilation_size ) );
 	cv::dilate(*src, dilation_dst, element );
	cv::imshow( "Dilation", dilation_dst );
}
void Morphology(int, void* userdata){
	cv::Mat morphology_dst;
	cv::Mat* src = static_cast<cv::Mat*>(userdata);
	int morphology_elem = cv::getTrackbarPos("Element", "Morphology");
	int morphology_size = cv::getTrackbarPos("Kernel", "Morphology");
	int morphology_oper = cv::getTrackbarPos("Operator", "Morphology");
	if( morphology_elem == 0 ){ morphology_elem = cv::MORPH_RECT; }
  	else if( morphology_elem == 1 ){ morphology_elem = cv::MORPH_CROSS; }
  	else if( morphology_elem == 2) { morphology_elem = cv::MORPH_ELLIPSE; }
  	else if( morphology_elem == 3) { morphology_elem = cv::MORPH_ELLIPSE; }
	cv::Mat element = cv::getStructuringElement(morphology_elem,
			cv::Size(2*morphology_size +1, 2*morphology_size+1),
			cv::Point(morphology_size, morphology_size));
	cv::morphologyEx(*src, morphology_dst, morphology_oper+2, element);
	cv::imshow("Morphology", morphology_dst); 
}
void erosion_dilation(cv::Mat* img){
	int const max_elem =3;
	int const max_kernel_size = 21;	
	cv::namedWindow ("Erosion", cv::WINDOW_AUTOSIZE);
	cv::namedWindow ("Dilation", cv::WINDOW_AUTOSIZE);
	cv::namedWindow ("Morphology", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Dilation", (*img).cols, 0);
	cv::createTrackbar("Element", "Erosion", nullptr, max_elem, Erosion, img);
	cv::createTrackbar("Kernel", "Erosion", nullptr, max_kernel_size, Erosion, img);
	cv::createTrackbar("Element", "Dilation", nullptr, max_elem, Dilation, img);
	cv::createTrackbar("Kernel", "Dilation", nullptr, max_kernel_size, Dilation, img);
	cv::createTrackbar("Element", "Morphology", nullptr, max_elem, Morphology, img);
	cv::createTrackbar("Kernel", "Morphology", nullptr, max_kernel_size, Morphology, img);
	cv::createTrackbar("Operator", "Morphology", nullptr, 4, Morphology, img);
	Erosion(0,img);
	Dilation(0,img);
	Morphology(0,img);
	//cv::setMouseCallback("Erosion", Erosion, *img);
}

int zoom(cv::Mat& img){
	for (;;){
	    	cv::imshow("Image", img);
	    	char c = (char)cv::waitKey(0);
	    	if (c == 27){break;}
	    	else if (c=='i'){
	    		cv::pyrUp(img, img, cv::Size(img.cols*2, img.rows*2));
	    		std::cout << "**Zoom In: Image x 2\n";
	    	}
	    	else if (c=='o'){
	    		cv::pyrDown(img, img, cv::Size(img.cols/2, img.rows/2));
	    		std::cout << "** Zoom Out: Image / 2 \n";
	    	}
	}
	return EXIT_SUCCESS;
}




void onTrackThreshold(int, void* userdata){
	cv::Mat* result = static_cast<cv::Mat*>(userdata);
	cv::Mat img = *result;
	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
	int threshold_value = cv::getTrackbarPos("Threshold Value", "Threshold");
	int threshold_type = cv::getTrackbarPos("Threshold Type", "Threshold");
	cv::threshold(gray, gray, threshold_value, 256, threshold_type); // 0-4
	cv::imshow("Threshold", gray);
}

void threshold_img(cv::Mat* img){
	
	cv::namedWindow("Threshold", cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Threshold Value", "Threshold", nullptr, 255, onTrackThreshold, img);
	cv::createTrackbar("Threshold Type", "Threshold", nullptr, 4, onTrackThreshold, img);
	onTrackThreshold(0, img);
}















