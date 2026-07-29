#pragma once
#include <string>
#include <memory>
class Vector2D {
	double* elements;
	double* first_free;
	double* cap;
	std::allocator<double> alloc;
	void check_alloc();
	std::pair<double*, double*> copy_alloc(const double* begin,const double* end);
	void reallocate();
	void free_alloc();
public:
	Vector2D() :elements{ nullptr }, first_free{ nullptr }, cap{ nullptr } {};
	Vector2D(std::initializer_list<double> list);
	Vector2D(const Vector2D& other);
	Vector2D& operator=(const Vector2D& other);
	void push_back(const double& str);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	double* begin() { return elements; }
	double* end() { return first_free; }

};