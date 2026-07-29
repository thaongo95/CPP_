#include "result.h"


Result::Result():
	text{ ""},
	line_nums{ std::make_shared<std::set<size_t>>()},
	lines{ std::make_shared<std::vector<std::string>>()}
{
}

Result::Result(std::string text, std::shared_ptr<std::set<size_t>> line_nums,
	std::shared_ptr<std::vector<std::string>> lines):
	text{ text },
	line_nums{ line_nums },
	lines{ lines }
{
}


std::ostream& operator<<(std::ostream& stream, const Result& result)
{
	stream << "\"" << result.text << "\"\n";
	for (auto line_num : *(result.line_nums)) {
		std::cout << "Line " << line_num << " : " << (*result.lines)[line_num] << std::endl;
	}
	return stream;
}

Result operator~(const Result& result)
{
	std::shared_ptr<std::set<size_t>> num_of_not{std::make_shared<std::set<size_t>>()};
	for (size_t i{ 0 }; i < result.lines->size(); i++) {
		num_of_not->insert(i);
	}
	for (auto it = result.line_nums->begin(); it != result.line_nums->end(); it++) {
		num_of_not->erase(*it);
	}

	return Result(result.text, num_of_not, result.lines);
}

Result operator&(const Result& result1, const Result& result2)
{
	std::string concat;
	concat += result1.text;
	concat += "\" and \"";
	concat += result2.text;
	std::shared_ptr<std::set<size_t>> num_of_and{ std::make_shared<std::set<size_t>>() };
	std::set_intersection(result1.line_nums->begin(), result1.line_nums->end(),
		result2.line_nums->begin(), result2.line_nums->end(),
		std::inserter(*num_of_and, num_of_and->begin()));
	return Result(concat, num_of_and, result1.lines);
}

Result operator|(const Result& result1, const Result& result2)
{
	std::string concat;
	concat += result1.text;
	concat += "\" or \"";
	concat += result2.text;
	std::shared_ptr<std::set<size_t>> num_of_or{ std::make_shared<std::set<size_t>>() };
	num_of_or->insert(result1.line_nums->begin(), result1.line_nums->end());
	num_of_or->insert(result2.line_nums->begin(), result2.line_nums->end());
	return Result(concat, num_of_or, result1.lines);
}
