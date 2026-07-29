// revisiting iterator

// Insert iterators: bind to a container and can be used to insert elements into the container
// Stream iterators: bind to input and output streams can be used to iterate through the associated IO stream
// Reverse iterators and Move iterators : special-purpose

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>

#define LOG(x) std::cout << x << std::endl;

void log_vt(const std::vector<int>& values) {
	std::for_each(values.begin(), values.end(), [](const int& value) {std::cout << value << " "; });
	std::cout << std::endl;
}

void get_sum(std::istream& stream) {
	std::istream_iterator<int> iter(stream);
	std::istream_iterator<int> end;  // it not init so have no value, like a .end() iterator
	int sum = std::accumulate(iter, end, 0);
	LOG(sum);
}

void read_file(const char* filename) {
	std::ifstream fin(filename);
	std::istream_iterator<std::string> iter2(fin), iter2_end;
	while (iter2 != iter2_end) {
		std::cout << *iter2++ << " ";    
	}
}
int main() {
	std::vector<int> vt_int{ 1,2,3,4,5,6,7,8,9 };
	std::vector<int> copy_1;
	std::vector<int> copy_2;
	std::reverse_copy(vt_int.begin(), vt_int.end(), std::back_inserter(copy_1));
	std::transform(vt_int.begin(), vt_int.end(), std::back_inserter(copy_2), [](const int& value) {return value + 10; });
	
	log_vt(vt_int);
	log_vt(copy_1);
	log_vt(copy_2);

	//get_sum(std::cin);
	read_file("text_txt");

	/*
			Iterator Categories
		Input iterator :               read, but not write; single-pass, increment only;
		Output iterator :			   write, but not read; single-pass, increment only;
		Forward iterator :			   Read and write; multi-pass, increment only;
		Bidirectinoal iterator :	   Read and write; multi-pass, increment and decrement;
		Random-access iterator :	   Read and write; multi-pass, full iterator arithmetic;
		    ALGORITHM PARAMETER PATTERNS
		alg (beg, end, other args);
		alg (beg, end, dest, other args);       -> dest commonly bound to an insert iterator or an ostream_iterator
		alg (beg, end, beg2, other args);       -> assume that the sequence beginning at beg2 is as large as the range denoted by beg and end.
		alg (beg, end, beg2, end2, other args);
	*/
	std::vector<int> copy_3;
	std::remove_copy_if(copy_1.begin(), copy_1.end(), std::back_inserter(copy_3), [](const int& value) { return value % 2 == 0; });
	log_vt(copy_3);

	auto end_of_remove = std::remove_if(copy_1.begin(), copy_1.end(), [](const int& value) { return value % 2 == 1; });
	log_vt(copy_1);    // generic algorithm can not remove element;
	
	copy_1.erase(end_of_remove, copy_1.end());
	log_vt(copy_1);   // must be use container operation;

	
}