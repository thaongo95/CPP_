#include "not_query.h"

void NotQuery::val(Finder& finder)
{
	auto result = finder.find(word);
	lines = result.lines;
	line_nums = result.line_nums;
	for (size_t i{ 0 }; i < lines->size(); i++) {
		not_line_nums->insert(i);
	}
	auto start = line_nums->begin();
	auto end = line_nums->end();
	while (start != end) {
		not_line_nums->erase(*start);
		start++;
	}
}

void NotQuery::print()
{
	std::cout << "\"" << word << "\"" << " not occur in line : " << lines->size() << std::endl;
	for (auto num : *not_line_nums)
		std::cout << "Line " << num << " : " << (*lines)[num] << std::endl;
}

NotQuery::NotQuery(const Query& query)
{
	word = query.word;
}

