#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>

#include <memory>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <sstream>



class Result {
	std::string text;
	std::shared_ptr<std::set<size_t>> line_nums;
	std::shared_ptr<std::vector<std::string>> lines;
	friend std::ostream& operator<<(std::ostream& stream, const Result& result);
	friend Result operator~(const Result& result);
	friend Result operator&(const Result& result1, const Result& result2);
	friend Result operator|(const Result& result1, const Result& result2);
public:
	Result();
	Result(std::string text, std::shared_ptr<std::set<size_t>> line_nums,
		std::shared_ptr<std::vector<std::string>> lines);
};