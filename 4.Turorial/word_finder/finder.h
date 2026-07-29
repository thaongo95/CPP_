#pragma once



#include "result.h"



class Finder {
	std::string input_file;
	std::map<std::string, std::shared_ptr<std::set<size_t>>> words;
	std::shared_ptr<std::vector<std::string>> lines{ std::make_shared<std::vector<std::string>>() };
public:
	Finder(const char* input_file);
	Result find(std::string word);
	
};