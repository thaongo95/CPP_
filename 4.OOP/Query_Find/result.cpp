#include "result.h"

Result::Result():
	lines{std::make_shared<std::vector<std::string>>()},
	line_nums{ std::make_shared<std::set<size_t>>()},
	word{""}
{
}

Result::Result(std::shared_ptr<std::vector<std::string>> lines, std::shared_ptr<std::set<size_t>> line_nums,
	std::string word):
	lines{lines}, line_nums{line_nums}, word{word}
{
}

Result::Result(const Result& other):
	lines{other.lines}, line_nums{other.line_nums}, word{word}
{
}
