#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "result.h"

class Finder {
	std::shared_ptr<std::vector<std::string>> lines{std::make_shared<std::vector<std::string>>()};
	std::map<std::string, std::shared_ptr<std::set<size_t>>> words;
public:
	Finder() = default;
	Finder(const std::string& filename);
	Result find(const std::string& word);
};