#include "word_query.h"

void WordQuery::val(Finder& finder)
{
	auto result = finder.find(word);
	lines = result.lines;
	line_nums = result.line_nums;
}

void WordQuery::print()
{
	std::cout << "\"" << word << "\"" << " occur in line : \n";
	for (int num : *line_nums) {
		std::cout << "Line " << num << " : " << (*lines)[num] << "\n";
	}
}

WordQuery::WordQuery(const std::string& word):
	word {word}
{
}

WordQuery::WordQuery(const WordQuery& query)
{
	word = query.word;
	lines = query.lines;
	line_nums = query.line_nums;
}


