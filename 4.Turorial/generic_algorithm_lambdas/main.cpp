#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// When lambdas capture variable:
void func1() {
	size_t local_val = 42;
	auto f = [local_val] {return local_val; };   // capture the value of variable at create time
	local_val = 0;
	auto f_result = f();
	std::cout << f_result << std::endl;
}
void func2() {
	size_t local_val = 42;
	auto f = [&local_val] {return local_val; };
	local_val = 0;
	auto f_result = f();                          // bounding by refence, capture value change when call function
	std::cout << f_result << std::endl;
}
void func3() {
	size_t local_val = 42;
	auto f = [local_val]() mutable {return ++local_val; };  // using mutable when changing the capture value
	local_val = 0;
	auto f_result = f();
	std::cout << f_result << std::endl;
}
void func4() {
	size_t local_val = 42;
	auto f = [&local_val] {return ++local_val; };
	local_val = 0;
	auto f_result = f();                                   // bouding by refence, change value when access from refence;
	std::cout << f_result << std::endl;
}

int main() {
	std::vector<std::string> vt{ "by", "dafault", "value", "the", "not", "change", "copy", "must", "we", "may", "that", "omit" };
	std::vector<std::string> vt_copy;

	std::transform(vt.begin(), vt.end(), std::back_inserter(vt_copy), [](std::string value) { return value + (std::string)"$"; }); // back_inserter() adding new element and return iterator
	// insert iterator operations is yields an iterator that adds element to specified continer
	std::for_each(vt_copy.cbegin(), vt_copy.cend(), [](const std::string& value) { std::cout << value << " "; });
	std::cout << std::endl;


	int  num = 4;
	auto f = [num](const std::string& value) -> bool {    //specifing the return type
		return value.size() >= 4;
		};
	for (auto element : vt) {
		std::cout << (f(element) ? element : (std::string)"---") << " " ;
	}
	std::cout << std::endl;
	
	std::for_each(vt.cbegin(), vt.cend(), [num](const std::string& value){
		std::cout << ((value.size() >= 4) ? "long" : "short") << " ";
		});
	std::cout << std::endl;

	auto counter = std::count_if(vt.begin(), vt.end(), f);    //counting the recallable f is true how many times
	std::cout << "count = " << counter << std::endl;
	
	std::for_each(vt.cbegin(), vt.cend(), [](const std::string& value) { std::cout << value << " "; });
	std::cout << std::endl;
	
	std::sort(vt.begin(), vt.end(), [](const std::string& value1, const std::string& value2) { return value1.size() < value2.size(); });
	                                             // dont need specifing the return type because the expression infer to return type
	std::for_each(vt.cbegin(), vt.cend(), [](const std::string& value) { std::cout << value << " "; });
	std::cout << std::endl;
	

	// How to change captured variable
	func1();
	func2();
	func3();
	func4();
}