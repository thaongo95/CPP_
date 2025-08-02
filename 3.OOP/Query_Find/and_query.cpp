#include "and_query.h"

AndQuery::AndQuery(const Query& query1, const Query& query2)
{
	word1 = query1.word;
	word2 = query2.word;
}

void AndQuery::val(Finder& finder)
{
	auto result1 = finder.find(word1);
	auto result2 = finder.find(word2);
	lines = result1.lines;
	std::set_intersection(result1.line_nums->begin(), result1.line_nums->end(),
		result2.line_nums->begin(), result2.line_nums->end(),
		std::inserter(*line_nums, line_nums->begin()));
}

void AndQuery::print()
{
	std::cout << "\"" << word1 << "\" and \"" << word2 << "\" occur in line : " << std::endl;
	for (auto num : *line_nums)
		std::cout << "Line " << num << " : " << (*lines)[num] << std::endl;
}

