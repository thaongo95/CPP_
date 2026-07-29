#include "finder.h"


Finder::Finder(const std::string& filename)
{
	std::ifstream fin(filename);
	std::string line;
	while (std::getline(fin, line)) {
		std::istringstream strin(line);
		lines->push_back(line);
		std::string word;
		while (strin >> word) {
			if (!words[word]) words[word] = std::make_shared<std::set<size_t>>();
			words[word]->insert(lines->size() - 1);
		}
	}
}

Result Finder::find(const std::string& word) 
{
	if (!words[word]) words[word] = std::make_shared<std::set<size_t>>();

	return Result(lines, words[word], word);
}
