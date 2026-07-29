#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <memory>

void print_result(const std::string& text,
	std::vector<std::string>& lines,
	std::map<std::string, int>& occurs, 
	std::map<std::string, std::set<int>>& line_nums) {
	if (occurs.find(text) == occurs.end()) {
		std::cout << "The word \"" << text << "\" not found" << std::endl;
	}
	else {
		std::cout << "The word \"" << text << "\"" <<
			((occurs[text] == 1) ? " occur " : " occurs ") <<
			occurs[text] << ((occurs[text] == 1) ? " time " : " times")
			<< std::endl;
		for (auto line_num : line_nums[text]) {
			std::cout << "\t (line " << line_num << ") " << lines[line_num - 1] << std::endl;
		}
	}

}
void get_text_query(const char* input, const std::string& text) {
	std::vector<std::string> lines;
	std::map<std::string, int> occurs;
	std::map<std::string, std::set<int>> line_nums;
	std::ifstream fin(input);
	std::string buffer;
	while (std::getline(fin, buffer)) {
		std::istringstream strin(buffer);
		lines.push_back(buffer);
		std::string word;
		while (strin >> word) {
			occurs[word]++;
			line_nums[word].insert(lines.size());
		}
	}
	print_result(text, lines, occurs, line_nums);
	/*if (occurs.find(text) == occurs.end()) {
		std::cout << "The word \"" << text << "\" not found" << std::endl;
	}
	else {
		std::cout << "The word \"" << text << "\"" <<
			((occurs[text] == 1) ? " occur " : " occurs ") <<
			occurs[text] << ((occurs[text] == 1) ? " time " : " times")
			<< std::endl;
		for (auto line_num : line_nums[text]) {
			std::cout << "\t (line " << line_num << ") " << lines[line_num-1] << std::endl;
		}
	}*/
}
class TextResult {
	std::shared_ptr<std::vector<std::string>> lines;
	std::shared_ptr<std::set<int>> line_numbers;
	int number;
public:
	TextResult(const int& number, std::shared_ptr<std::set<int>> line_numbers,
		std::shared_ptr<std::vector<std::string>> lines) :number{ number },
		line_numbers{ line_numbers }, lines{ lines }{}
	void print_result(const std::string& text) {
		std::cout << "The word \"" << text << "\"" <<
			((number == 1) ? " occur " : " occurs ") <<
			number << ((number == 1) ? " time " : " times")
			<< std::endl;
		for (auto line_num : *line_numbers) {
			std::cout << "\t (line " << line_num << ") " << lines->at(line_num) << std::endl;
		}
	}
};

class TextQuery {
	std::shared_ptr<std::vector<std::string>> lines = std::make_shared<std::vector<std::string>>();
	std::map<std::string, int> occurs;
	std::map<std::string, std::shared_ptr<std::set<int>>> line_numbers;
public:
	TextQuery(char const* filename) {
		std::ifstream read_file(filename);
		std::string buffer;
		while (std::getline(read_file, buffer)) {
			std::istringstream strin(buffer);
			lines->push_back(buffer);
			std::string word;
			while (strin >> word) {
				occurs[word]++;
				auto &line_nums = line_numbers[word];
				if (!line_nums) line_nums.reset(new std::set<int>);
				line_nums->insert(lines->size() - 1);
			}
		}
	}
	void getResult(const std::string& text) {
		if (occurs.find(text) == occurs.end()) {
			std::cout << "The word \"" << text << "\" not found" << std::endl;
		}
		else {
			TextResult result(occurs[text], line_numbers[text], lines);
			result.print_result(text);
		}
	}	
};

int main() {
	auto start1 = std::chrono::high_resolution_clock::now();
	/*               METHOD 1             */
	//get_text_query("texts.txt", "to");
	/*               METHOD 2             */
	TextQuery query("texts.txt");
	query.getResult("to");
	auto end1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> during_time = end1 - start1;
	std::cout << "Finished in " << during_time.count() * 1000.00f << " ms" << std::endl;
}