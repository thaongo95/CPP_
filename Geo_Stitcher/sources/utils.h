#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <cmath>
struct ImageData{
	int id;
	std::string name;
	double lat = 0.0, lng = 0.0, alt = 0.0;
};

std::vector<std::string> getImagesInFolder(const std::string& folderPath);
std::vector<ImageData> parseCSV(const std::string& csv_path);
double gps_distance(double lat1, double lon1, double lat2, double lon2);
double haversine_distance(double lat1, double lon1, double lat2, double lon2);

#endif
