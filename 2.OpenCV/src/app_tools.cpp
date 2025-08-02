#include "app_tools.h"
#include <iostream>



void imgInfo(const cv::Mat& img){
	std::cout << "Dimension: (cols and rows): " << img.cols << "x" << img.rows << std::endl;
	std::cout << "Size [W x H]:               " << img.size() << std::endl;
	std::cout << "Channels:                   " << img.channels() << std::endl;
	std::cout << "Mat type (enum):            " << img.type() << std::endl;
	std::cout << "Total pixels:               " << img.total() << std::endl;
	std::cout << "Is continuous:              " << (img.isContinuous() ? "Yes" : "No") << std::endl;
	std::cout << "Step (byte per row):        " << img.step << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;

}


cv::Mat read_img(const std::string& name){
	cv::Mat img = cv::imread(image_path+name, cv::IMREAD_COLOR);
	if (img.empty()) {
        	std::cout << "Could not read the image: " << image_path << std::endl;
        }
        return img;
}
void save_img(const std::string& name, const cv::Mat& image){
	bool success_ = cv::imwrite(save_image_path+name, image);
	if (success_) {
        	std::cout << "Save image " << name << " to the path:  \"" << save_image_path <<  "\"" << std::endl;
        }
        else {
        	std::cout << "Fail to save image" << std::endl;
        }
}
