#include <string>
#include <iostream>

std::string::size_type find_char(const std::string &s, char c, std::string::size_type &occurs)
{
	auto ret = s.size();
	occurs = 0;
	for (decltype(ret) i = 0; i != s.size(); ++i){
		if (s[i] == c){
			if (ret == s.size())
				ret = i;
			++occurs;
		}
	}
	return ret;
}

void run_find_char(){
	std::string s;
	char c;
	std::cout << "input your string here: " << std::endl;
	getline(std::cin, s);
	std::cout << "input your charecter here: " << std::endl;
	std::cin >> c;
	std::string::size_type occurs;
	std::cout << "first charecter position: " <<  find_char(s, c, occurs) << std::endl;
	std::cout << "total appearences: " << occurs << std::endl;
}

