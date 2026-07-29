#include <iostream>
#include "utils.h"

void do_something(){
	std::cout << "Pass" << std::endl;
}

std::vector<std::string> getImagesInFolder(const std::string& folderPath) {
    std::vector<std::string> files;
    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(folderPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string filename = ent->d_name;

            // Skip "." and ".."
            if (filename == "." || filename == "..") 
                continue;

            // Filter image extensions
            if (filename.find(".jpg") != std::string::npos ||
                filename.find(".png") != std::string::npos ||
                filename.find(".JPG") != std::string::npos ||
                filename.find(".jpeg") != std::string::npos) 
            {
                files.push_back(folderPath + "/" + filename);
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }

    return files;
}

std::vector<ImageData> parseCSV(const std::string& csv_path){
	std::ifstream file(csv_path);
	if (!file.is_open()){std::cerr << "ERROR" << std::endl;}
	std::string line;
	int count=0;
	std::vector<ImageData> image_datas;
	while (std::getline(file, line)){
		std::stringstream ss(line);
		std::string item;
		ImageData data;
		if (count==0) { count++;}
		else {
			data.id = count-1;
			std::getline(ss, item, ','); data.name = item;
			std::getline(ss, item, ','); data.lat = std::stod(item);
			std::getline(ss, item, ','); data.lng = std::stod(item);
			std::getline(ss, item, ','); data.alt = std::stod(item);
			image_datas.push_back(data);
			count++;
		}
	}
	return image_datas;
}

double gps_distance(double lat1, double lon1, double lat2, double lon2) {
    double r = 6371e3; // meters
    double phi1 = lat1 * M_PI / 180.0;
    double phi2 = lat2 * M_PI / 180.0;
    double delta_phi = (lat2 - lat1) * M_PI / 180.0;
    double delta_lambda = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(delta_phi / 2) * sin(delta_phi / 2) + cos(phi1) * cos(phi2) * sin(delta_lambda / 2) * sin(delta_lambda / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return r * c;
}

double haversine_distance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371000; // Earth's radius in meters
    double lat1_rad = lat1 * M_PI / 180.0;
    double lon1_rad = lon1 * M_PI / 180.0;
    double lat2_rad = lat2 * M_PI / 180.0;
    double lon2_rad = lon2 * M_PI / 180.0;

    double dlon = lon2_rad - lon1_rad;
    double dlat = lat2_rad - lat1_rad;

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1_rad) * cos(lat2_rad) *
               sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}


