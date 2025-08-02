#include "or_query.h"

OrQuery::OrQuery(const Query& query1, const Query& query2)
{
	word1 = query1.word;
	word2 = query2.word;
	
}

void OrQuery::val(Finder& finder)
{
	auto result1 = finder.find(word1);
	auto result2 = finder.find(word2);
	lines = result1.lines;
	line_nums->insert(result1.line_nums->begin(), result1.line_nums->end());
	line_nums->insert(result2.line_nums->begin(), result2.line_nums->end());
}

void OrQuery::print()
{
	std::cout << "\"" << word1 << "\" or \"" << word2 << "\" occur in line : " << std::endl;
	for (auto num : *line_nums)
		std::cout << "Line " << num << " : " << (*lines)[num] << std::endl;
}
