#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

struct Price_of_item {
	std::string item;
	double price;
	Price_of_item(std::string i, double p) : item{ i }, price{ p } {}
	bool operator<(const Price_of_item& other) const {
		return price < other.price;
	}
};

void init_order_map() {
	std::vector<std::string> items = { "book", "pencil", "yardstick", "rule", "erase", "fish", "car" , "adaptor", "phone" };
	std::vector<double> price = { 12.99, 3.99, 15.99, 4.99, 2.99, 8.99, 1200.00, 23.99, 399.99 };
	std::map<Price_of_item, size_t> Bills;
	for (size_t i{ 0 }; i < 9; i++) {
		Price_of_item POI = Price_of_item(items[i], price[i]);
		Bills[POI]++;
	}
	for (auto bill : Bills) {
		std::cout << bill.first.item << " : " << bill.first.price << " : " << bill.second << std::endl;
	}
}

void get_word_from_file(const char* inputfile, const char* outputfile) {
	std::string line;
	std::ifstream fin(inputfile);
	std::map<std::string, size_t> words_static;
	std::set<std::string> useless_words{ "the", "a", "and", "or", "an", "but", "The", "A", "And", "An", "Or", "But" };
	while (std::getline(fin, line)) {
		std::istringstream in_string(line);
		std::string word;
		while (in_string >> word) {
			if (useless_words.find(word) != useless_words.end())
				words_static[word]++;
		}
	}
	std::ofstream fout(outputfile);
	for (auto word : words_static) {
		fout << "\"" << word.first << "\"" << " appear " << word.second << ((word.second > 1) ? " times" : " time") << std::endl;
	}
}

void get_word_from_cin() {
	std::map<std::string, int> people;
	std::string buffer;
	while (std::cin >> buffer) {
		++people[buffer];
		if (buffer == "end") break;
	}
	for (auto person : people) {
		std::cout << person.first << " come for " << person.second  << ((person.second>1) ? " times" : " time") << std::endl;
	}
}


void transform_words(const std::string& input, const std::string& output, const std::string& trans_map) {
	
	std::ifstream fin(trans_map);
	std::string line;
	std::map<std::string, std::string> shorthand_replace;
	while (std::getline(fin, line)) {
		auto it = line.begin();
		while (it != line.end()) {
			if ((*it) == '-') {
				std::string first, second;
				std::copy(line.begin(), it - 1, std::back_inserter(first));
				std::copy((it + 2), line.end(), std::back_inserter(second));
				shorthand_replace[first] = second;
			}
			it++;
		}
	}
	fin.close();
	fin.open(input);
	std::ofstream fout(output);
	while (std::getline(fin, line)) {
		std::istringstream strin(line);
		std::ostringstream strout;
		std::string word;
		while (strin >> word) {
			std::set<char> special_char = { ':', ',', '!', '?', '.' };
			std::string tail = "";
			if (special_char.find(*(word.end() - 1)) != special_char.end()) {
				tail += *(word.end() - 1);
				word.erase(word.end() - 1);
			}
			strout << ((shorthand_replace.find(word)!=shorthand_replace.end()) 
				      ? shorthand_replace[word] : word) << tail << " ";
		}
		strout << std::endl;
		fout << strout.str();
	}

}
int main() {
	
	//get_word_from_cin();
	//get_word_from_file("text.txt", "static2.txt");
	//init_order_map();
	transform_words("input.txt", "output.txt", "shorthand.txt");


}