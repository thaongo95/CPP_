#include "finder.h"
#include "result.h"

int main() {
	Finder finder("input.txt");
	auto result = finder.find("they");
	auto result2 = finder.find("a");
	auto result3 = finder.find("an");
	std::cout << (result & result2 | result3) << std::endl;
}