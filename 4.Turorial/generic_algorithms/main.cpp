#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>

int count(const std::vector<int>::iterator& begin,const std::vector<int>::iterator& end, const int& value) { // read-only function
	int T = 0;
	for (auto i = begin; i != end; i++) {
		if (value == (*i)) T++; // Iterators make the Algorithm container independent, but the container has to have COMPARISION operation 
	}
	return T;
}

int count(std::string::iterator begin, std::string::iterator end, const char& value) {
	int T = 0;
	for (auto i = begin; i != end; i++) {
		if (value == (*i)) T++;   // we can do that kind of operate is because the container is continue address
	}
	return T;
}

int count(int* begin, int* end, const int& value) {
	int T = 0;
	for (auto i = begin; i != end; i++) {
		if (value == (*i)) T++;
	}
	return T;
}



void getUnique(std::vector<int>& values) {
	std::sort(values.begin(), values.end());   // must be sort before unique
	std::for_each(values.begin(), values.end(), [](const int& value) {std::cout << value << " "; });  // same as for (auto value : values) std::cout << value << " ";
	std::cout << std::endl;
	auto unique_endpoint = std::unique(values.begin(), values.end()); // reorder the unique value to the fisrt part and the function return is the last unique value iterator                                                 
	for (auto value : values) std::cout << value << " ";
	std::cout << std::endl;
	values.erase(unique_endpoint, values.end());     // erase is container operation so it can delete element from the last unique value to the end.
	auto pos = std::find_if(values.begin(), values.end(), [](const int& value) {return value >= 5; });
	for (auto value : values) std::cout << value << " ";
	std::cout << std::endl;
	std::cout << values.end() - pos << std::endl;
}

void stableSort(std::vector<std::string>& values) {
	std::sort(values.begin(), values.end());
	for (auto value : values) std::cout << value << " ";
	std::cout << std::endl;
	std::sort(values.begin(), values.end(), [](const std::string& a,const std::string& b) {return a.size() < b.size(); });
	//std::stable_sort(values.begin(), values.end(), [](std::string a, std::string b) {return a.size() < b.size(); });
	for (auto value : values) std::cout << value << " ";
	std::cout << std::endl;

}


int main() {
	// The algorithms dont work directly on a container, it operate by traversing a RANGE OF ELEMENT bounded by TWO ITERATORS
	std::cout << "********************VECTOR******************" << std::endl;
	std::vector<int> vt_1{ 1,2,3,4,5,6,7,8,8,8,8,5,6,7,4,5,6,3,4,5,10,11,12,13,14,15,16,9,1,2,3,4,5,6,7,8,9 };
	std::vector<std::string> vt_2{ "contains", "order", "animal" , "those", "by", "vector", "the", "same", "to", "be", "we", "can", "sort", "they", "quick", "slow", "red", "fox" };
	int num_1 = 4;
	auto result_1 = std::find(vt_1.begin(), vt_1.end(), num_1);
	auto count_result_1 = count(vt_1.begin(), vt_1.end(), num_1);
	auto accumulate_result_1 = std::accumulate(vt_1.begin(), vt_1.end(), 0); //the third param is used for init sum = 0;
	std::cout << "Number " << num_1 << " " << ((result_1 != vt_1.end()) ? "is present" : "is not present") << " ";
	std::cout << count_result_1 << " times" << std::endl;
	std::cout << "Sum : " << accumulate_result_1 << std::endl;
	getUnique(vt_1);
	stableSort(vt_2);

	std::cout << std::endl;

	std::cout << "********************STRING*********************" << std::endl;
	std::string str_1{ "a value of string" };
	char ch_1 = 'o';
	auto result_2 = std::find(str_1.begin(), str_1.end(), ch_1);
	auto count_result_2 = count(str_1.cbegin(), str_1.cend(), ch_1); // passing the const iterator;
	auto accumulate_result_2 = std::accumulate(str_1.begin(), str_1.end(), (std::string)"Concat all emelemt: "); // accumulate algorithm present the '+' operation
	std::cout << "Character " << ch_1 << " " << ((result_2 != str_1.end()) ? "is present" : "is not present") << " ";
	std::cout << count_result_2 << " times" << std::endl;
	std::cout << accumulate_result_2 << std::endl;

	std::cout << std::endl;

	std::cout << "****************BUILT-IN ARRAY****************" << std::endl;
	// This work for the built-in array, becauce in built-in array pointer act like iterator
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int num_2 = 10;
	//std::fill_n(std::begin(a), 5, 0);
	auto result_3 = std::find(std::begin(a), std::end(a), num_2);
	auto count_result_3 = count(std::begin(a), std::end(a), num_2);
	auto accumulate_result_3 = std::accumulate(std::begin(a), std::end(a), 0);
	std::sort(std::begin(a), std::end(a), [](int a, int b) {return a > b; });
	for (int i{ 0 }; i < 10; i++) std::cout << a[i] << " ";
	std::cout << std::endl;
	std::cout << "Number " << num_2 << " " << ((result_3 != std::end(a)) ? "is present" : "is not present") << " ";
	std::cout << count_result_3 << " times" << std::endl;
	std::cout << "Sum : " << accumulate_result_3 << std::endl;
	int b[sizeof(a)/sizeof(*a)];
	auto ret = std::copy(std::begin(a), std::end(a), b);
	auto result_equal = std::equal(std::begin(a), std::end(a), std::begin(b));
	std::cout << ((result_equal) ? "Equal" : "Not equal") << std::endl;
	std::replace(std::begin(b), std::end(b), 9, 12);
	result_equal = std::equal(std::begin(a), std::end(a), std::begin(b));
	std::cout << ((result_equal) ? "Equal" : "Not equal") << std::endl;
	




}