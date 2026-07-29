#include <iostream>
#include "strvec.h"



int main() {
	StrVec vt1{"hello"};
	std::string str("sdasdasd");
	vt1.push_back("snkk");
	vt1.push_back(str);
	vt1.push_back("dhjaskdas");
	StrVec vt2{ "hello", "csds", "dasd", "dasd" };
	StrVec vt3, vt4;
	vt3 = { "jdas", "das", "das", "das", "das" };
	vt4 = vt1;
	std::cout << vt1.size() << std::endl;
	std::cout << vt2.size() << std::endl;
	std::cout << vt3.size() << std::endl;
	std::cout << vt4.size() << std::endl;
}