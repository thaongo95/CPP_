#include <iostream>
#include <string>
#include <vector>

#define LOG(x) std::cout << x << std::endl


int findInt(std::vector<int>::iterator begin,
	const std::vector<int>::iterator end, const int& number) {
	bool flag{ false };
	int count{ 0 };
	while (begin != end) {               //dont cache the iterator returned from end() in loops that insert or delete element in a deque, string, vector
		if (*begin == number) {
			flag = true; break;
		}
		++begin;
		++count;
	}
	if (flag) return count;
	else return -1;
}

void string_init() {

	LOG("String is a vector of char ??");
	LOG("");
	std::string str1 = { "library container" };       // When we initialize a container as a copy of another container,
	// the container type and element type of both containers must be identical.

	std::string str2(str1);     
	std::string str3(str1.begin(), str1.begin() + 7);   // this is copy 
	std::string str4{ 's', 'h', 'a' ,' ', 'b', 'i' };
	LOG(str1); LOG(str2); LOG(str3); LOG(str4); LOG("");
	
	str2.swap(str4);
	str4.assign(str2.cbegin(), str2.cbegin()+5);
	str4.assign({ 'd', 'f', 'f', 'h', 'j' });
	str4.assign(10, '!');

	std::string::iterator begin = str3.begin();
	std::string::iterator end = str3.end();
	while (begin != end) {  // this is why a container is [) style;
		*begin = '*';
		++begin;
	}

	for (auto i = str1.begin(); i != str1.end(); i++) {
		*(i) = '$';
	}

	LOG(str1); LOG(str2); LOG(str3); LOG(str4); LOG("");

	str3.clear(); str3 = std::string(10, '@'); // contruction that pass in the size and an (optional) element initializer
	str2.insert(str2.begin(), { 'D', 'a', ' ' });
	str2.insert(str2.begin(), str3.begin() + 2, str3.begin() + 5);
	str1.erase(str1.begin() + 2, str1.begin() + 8);

	LOG(str1); LOG(str2); LOG(str3); LOG(str4); LOG("");

	std::cout << "size of string :" << str1.size() << "-" << str2.size() << "-" << str3.size() << "-" << str4.size() << std::endl;
	std::cout << "EMPTY? : " << ((str1.empty()) ? "str1 is empty" : " str1 not empty ")
		<< ((str2.empty()) ? "str2 is empty" : " str2 not empty ")
		<< ((str3.empty()) ? "str3 is empty" : " str3 not empty ")
		<< ((str4.empty()) ? "str4 is empty" : " str4 not empty ") << std::endl;
}

int main() {
	std::vector<int> vt = { 1,3,2,3,4,5,6,7,8,1,5 };
	int result = findInt(vt.begin() + 3, vt.begin() + 8, 3);
	LOG("Find element in vector !");
	if (result >= 0) std::cout << "element[" << 3 + result << "] : " << vt[3 + result] << std::endl;
	else LOG("Not found");
	LOG("");

	string_init();

	std::string s{ 'a', 'b', 'c', 'd', 'e' };
	LOG("Input char");
	auto first = s.begin();
	char ch;
	while (std::cin >> ch) {
		first = s.insert(first, ch);
		if (ch == 'q') break;
	}
	LOG(s);

	LOG("The size and capacity og string s : ");
	LOG(s.capacity());
	LOG(s.size());
	s.reserve(50);
	LOG("The size and capacity og string s : ");
	LOG(s.capacity());
	LOG(s.size());
	while (s.size() != s.capacity()) {
		s.push_back('0');
	}
	LOG("The size and capacity og string s : ");
	LOG(s.capacity());
	LOG(s.size());
	s.push_back('2');
	LOG("The size and capacity og string s : ");
	LOG(s.capacity());
	LOG(s.size());
	s.shrink_to_fit();
	LOG("The size and capacity og string s : ");
	LOG(s.capacity());
	LOG(s.size());
}