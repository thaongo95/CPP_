
#include "image_functions.h"


cv::Mat canny_detection(const cv::Mat& image){
	cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        cv::Mat blur;
        cv::GaussianBlur(gray, blur, cv::Size(5,5), 1.5);

        cv::Mat canny;
        double low_threshold = 150;
        double high_threshold = 300;
        cv::Canny(blur, canny, low_threshold, high_threshold);

        return canny;
}

cv::Mat edge_detection(const cv::Mat& image, const double& area_threshold){
	cv::Mat edges, img;
	edges = canny_detection(image);
	image.copyTo(img);
	
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	
	for (const auto& contour:contours){
		double area = cv::contourArea(contour);
		if (area < area_threshold) continue;
		
		std::vector<cv::Point> approx;
		cv::approxPolyDP(contour, approx, 0.02 * cv::arcLength(contour, true), true);
		cv::drawContours(img, std::vector<std::vector<cv::Point>>{approx}, -1, {0,255,0}, 2);
		std::string shapeType;
		int v = approx.size();
		if (v == 3) shapeType = "Triangle";
		else if (v == 4) {
		    cv::Rect r = cv::boundingRect(approx);
		    float aspect = (float)r.width / r.height;
		    shapeType = (aspect > 0.95 && aspect < 1.05) ? "Square" : "Rectangle";
		}
		else if (v > 6) shapeType = "Circle";

		// Draw label
		cv::putText(img, shapeType, approx[0], cv::FONT_HERSHEY_SIMPLEX, 0.6, {0,0,255}, 2);
		}
	return img;
}	


//std::pair<std::vector<cv::KeyPoint>, cv::Mat> 
auto orb_detection(const cv::Mat& image,const int& nfeatures){ //input the gray image and the nfeatures
	cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(nfeatures);
	std::vector<cv::KeyPoint> keypoints;
	cv::Mat descriptors;
	orb_detector->detectAndCompute(image,cv::noArray(), keypoints, descriptors);
	std::cout << "Found " << keypoints.size() << " keypoints" << std::endl;
	std::cout << "Descriptor matrix size: " << descriptors.rows << " x " << descriptors.cols << std::endl;
	cv::Mat img_with_kp;
	cv::drawKeypoints(image, keypoints, img_with_kp, cv::Scalar(0, 255, 0), cv::DrawMatchesFlags::DEFAULT);
	//cv::imshow("ORB Keypoints", img_with_kp);
	return std::make_pair(keypoints, descriptors);
}


cv::Mat image_matching(const cv::Mat& object_img,const cv::Mat& scene_img,const int& nfeatures){ //input gray images
	
	cv::Mat object, scene;
    	cv::cvtColor(object_img, object, cv::COLOR_BGR2GRAY);
    	cv::cvtColor(scene_img, scene, cv::COLOR_BGR2GRAY);
	auto object_orb = orb_detection(object, nfeatures);
	auto scene_orb = orb_detection(scene, nfeatures);
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE_HAMMING);

	std::vector<std::vector<cv::DMatch>> knn_matches;
	matcher->knnMatch(object_orb.second, scene_orb.second, knn_matches, 2);

	std::vector<cv::DMatch> good_matches;
	const float ratio_thresh = 0.75f;
	for (size_t i=0; i< knn_matches.size(); i++){
		good_matches.push_back(knn_matches[i][0]);
	}

	std::cout<< "Found " << good_matches.size() << " good matches" << std::endl;

	// Visualize
	cv::Mat img_matches;
	cv::drawMatches(object, object_orb.first, scene, scene_orb.first, good_matches, img_matches,
			cv::Scalar::all(-1), cv::Scalar::all(-1), std::vector<char>(),
			cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	if (good_matches.size() >= 4){
		std::vector<cv::Point2f> obj_points;
		std::vector<cv::Point2f> scene_points;

		for(const auto& match : good_matches){
			obj_points.push_back(object_orb.first[match.queryIdx].pt);
			scene_points.push_back(scene_orb.first[match.trainIdx].pt);
		}
		cv::Mat H = cv::findHomography(obj_points, scene_points, cv::RANSAC);

		std::vector<cv::Point2f> obj_corners(4);
		obj_corners[0] = cv::Point2f(0,0);
		obj_corners[1] = cv::Point2f((float)object.cols,0);
		obj_corners[2] = cv::Point2f((float)object.cols,(float)object.rows);
		obj_corners[3] = cv::Point2f(0,(float)object.rows);

		std::vector<cv::Point2f> scene_corners(4);
		cv::perspectiveTransform(obj_corners, scene_corners, H);
		cv::Point2f offset((float)object.cols, 0);
		cv::line(img_matches, scene_corners[0] + offset, scene_corners[1] + offset, cv::Scalar(0, 0, 255), 4);
	        cv::line(img_matches, scene_corners[1] + offset, scene_corners[2] + offset, cv::Scalar(0, 0, 255), 4);
	        cv::line(img_matches, scene_corners[2] + offset, scene_corners[3] + offset, cv::Scalar(0, 0, 255), 4);
        	cv::line(img_matches, scene_corners[3] + offset, scene_corners[0] + offset, cv::Scalar(0, 0, 255), 4);

	
	}
	
	//cv::imshow("Result" , img_matches);
	return img_matches;

}

cv::Mat color_detection(const cv::Mat& object, const double& erea_threshold, const Color& color_){
	cv::Mat img, hsv_img;
	object.copyTo(img);
	cv::cvtColor(object, hsv_img, cv::COLOR_BGR2HSV);
	cv::Mat mask;
	switch(color_){
		case Color::RED:{
			cv::Scalar lower_red1(0, 100, 100), upper_red1(10, 255, 255);
			cv::Scalar lower_red2(160, 100, 100), upper_red2(179, 255, 255);
			cv::Mat mask1, mask2;
			cv::inRange(hsv_img, lower_red1, upper_red1, mask1);
			cv::inRange(hsv_img, lower_red2, upper_red2, mask2);
			cv::bitwise_or(mask1, mask2, mask);
			break;}
		case Color::GREEN:{
			cv::Scalar lower_green(35, 100, 100);
			cv::Scalar upper_green(85, 255, 255);
			cv::inRange(hsv_img, lower_green, upper_green, mask);	
			break;}
		case Color::BLUE:{
			cv::Scalar lower_blue(100, 100, 100);
			cv::Scalar upper_blue(130, 255, 255);
			cv::inRange(hsv_img, lower_blue, upper_blue, mask);

			break;}
		case Color::YELLOW:{
			cv::Scalar lower_yellow(20, 100, 100);
			cv::Scalar upper_yellow(30, 255, 255);
			cv::inRange(hsv_img, lower_yellow, upper_yellow, mask);

			break;}
		case Color::BLACK:{
			cv::Scalar lower_black(0, 0, 0);
			cv::Scalar upper_black(180, 255, 50);
			cv::inRange(hsv_img, lower_black, upper_black, mask);
			break;}
	}
	
	
	cv::erode(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));	
	cv::dilate(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
	
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (size_t i=0; i< contours.size(); i++){
		double erea = cv::contourArea(contours[i]);
		if (erea > erea_threshold){
			cv::Rect bounding_rect = cv::boundingRect(contours[i]);
			cv::rectangle (img, bounding_rect, cv::Scalar(0,255,0), 2);
		}
	}
	return img;
}

