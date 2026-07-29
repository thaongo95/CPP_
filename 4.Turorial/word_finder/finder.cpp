#include "finder.h"


Finder::Finder(const char* input_file) 
	:input_file{ input_file }
{
	std::ifstream fin(input_file);
	std::string line;	
	while (std::getline(fin, line)) {
		lines->push_back(line);
		std::istringstream str_in(line);
		std::string word;
		while (str_in >> word) {
			if (!words[word]) words[word] = std::make_shared<std::set<size_t>>();
			words[word]->insert(lines->size()-1);
		}
	}
}

Result Finder::find(std::string word)
{
	if (!words[word])
		words[word] = std::make_shared<std::set<size_t>>();
	return Result(word, words[word], lines);
}

