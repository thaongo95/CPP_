#include <iostream>
#include "vector2D.h"


int main() {
	Vector2D vt = { 1,2,3,4.5 };
	vt.push_back(1);
	vt.push_back(2);
	vt.push_back(3);
	vt.push_back(4);
	vt.push_back(5);
	Vector2D vt2;
	vt2 = vt;
	auto it = vt2.begin();
	std::cout << vt2.size() << std::endl;
	while (it != vt2.end()) {
		std::cout << *it++ << std::endl;
	}
}