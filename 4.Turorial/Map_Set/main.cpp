#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>


void print_map(const std::map<std::string, int>::iterator& begin, const std::map<std::string, int>::iterator& end) {
	std::map<std::string, int>::iterator it = begin;
	while (it != end) {
		std::cout << "\"" << it->first  << "\"" << " "
			<< it->second << ((it->second>1) ? " times" : " time") << std::endl;
		it++;
	}
}

void count_words(std::string input) {
	std::ifstream fin(input);
	std::string line;
	std::map<std::string, int> texts;

	while (std::getline(fin, line)) {
		std::istringstream strin(line);
		std::string word;
		while (strin >> word) {
			texts[word]++;
		}
	}
	print_map(texts.begin(), texts.end());
	std::cout << texts["the"] << std::endl;
	std::pair<std::map<std::string, int>::iterator, bool> ret = texts.insert(std::make_pair("anhh", 3));
	std::cout << (ret.first)->second << std::endl; // hold the insert pair, if pair existed then the value insert invalid, if not existed then the new pair is created
	std::cout << ret.second << std::endl;       // bool value, if pair existed then return 0 (no insert), if not exist return 1;
	std::cout << "size before remove : " << texts.size() << std::endl;
	std::set<std::string> remove_words{ "the", "of", "by", "a", "an", "but" };
	auto it = texts.begin();
	while (it != texts.end()) {
		if (remove_words.find((it)->first) != remove_words.end()) {
			it = texts.erase(it);
		}
		else it++;
	}
	std::cout << "size after remove : " << texts.size() << std::endl;
}

void author_with_books(std::string input) {
	std::ifstream fin(input);
	std::string line;
	std::map<std::string, std::vector<std::string>> author_books;
	std::multimap<std::string, std::string> authors_books;
	while (std::getline(fin, line)) {
		std::string temp{ "" };
		auto it = line.begin();
		std::string book, author;
		while (it != line.end()) {
			if (*it == ':' || *it == ';') {
				book= temp;
				temp = "";
			}
			else {
				temp += (*it);
			}
			it++;
		}
		author = temp;
		author_books[author].push_back(book); // if the key not already present, a new element is created and inserted into the map for that key;
		//authors_books[author] = book; can not subcript a multimap because more than one value associated with a given key;
		authors_books.insert({ author, book });
	}
	std::cout << "map size : " << author_books.size() << std::endl;
	std::cout << "multi map size: " << authors_books.size() << std::endl;
	std::cout << "map size : " << author_books.count("Chetan Bhagat") << std::endl;
	std::cout << "multi map size: " << authors_books.count("Chetan Bhagat") << std::endl;
	
	/*auto it = author_books.begin();
	while (it != author_books.end()) {
		std::cout << (it++)->first << std::endl;
	}*/
	std::cout << author_books["Chetan Bhagat"].size() << std::endl;
	std::cout << ((author_books.find("Chetan Bhagat")!=author_books.end()) ? "Found" : "Not Found") << std::endl;
	
	auto lower_key = authors_books.lower_bound("Chetan Bhagat");
	auto upper_key = authors_books.upper_bound("Chetan Bhagat");
	std::cout << lower_key->second << std::endl;
	std::cout << upper_key->second << std::endl;

	auto equal_key = authors_books.equal_range("Chetan Bhagat"); // it is a pair
	std::cout << equal_key.first->second << std::endl;
	std::cout << equal_key.second->second << std::endl;
}

void word_transformation(const char* input, const char* output) {
	std::map<std::string, std::string> trans_map{
		{"brb", "be right back"},
		{"k", "okay?"},
		{"y", "why" },
		{"r", "are"},
		{"u" ,"you"},
		{"pic" ,"picture"},
		{"thk", "thanks!"},
		{"l8r" ,"later"},
	};
	std::ifstream fin(input);
	std::ofstream fout(output);
	std::string line;
	while (std::getline(fin,line)) {
		std::istringstream strin(line);
		std::ostringstream strout;
		std::string word;
		while (strin >> word) {
			strout << ((trans_map.find(word)!= trans_map.end()) ? trans_map[word] : word) << " ";
		}
		fout << strout.str() << std::endl;
	}

}
int main() {
	//count_words("text.txt");
	//author_with_books("books.txt");
	word_transformation("input.txt", "output.txt");
}