#pragma once

#include <vector>
#include <map>
#include <set>
#include <string>
#include <memory>


class Result {
	

public:
	std::shared_ptr<std::vector<std::string>> lines;
	std::shared_ptr<std::set<size_t>> line_nums;
	std::string word;
	Result();
	Result(std::shared_ptr<std::vector<std::string>> lines, std::shared_ptr<std::set<size_t>> line_nums, std::string word);
	Result(const Result& other);

};