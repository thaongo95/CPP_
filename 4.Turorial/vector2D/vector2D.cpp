#include "vector2D.h"

void Vector2D::check_alloc()
{
	if (size() == capacity()) {
		reallocate();
	}
}

std::pair<double*, double*> Vector2D::copy_alloc(const double* begin, const double* end)
{
	auto data = alloc.allocate(end - begin);
	return { data, std::uninitialized_copy(begin, end, data) };
}

void Vector2D::reallocate()
{
	int new_size = (size()) ? size() * 2 : 1;
	auto newdata = alloc.allocate(new_size);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i{ 0 }; i < size(); i++) {
		alloc.construct(dest++, std::move(*elem++));
	}
	free_alloc();
	elements = newdata;
	first_free = dest;
	cap = newdata + new_size;
}

void Vector2D::free_alloc()
{
	if (elements) {
		auto it = first_free;
		while (it != elements) {
			alloc.destroy(--it);
		}
		alloc.deallocate(elements, cap - elements);
	}
	
}

Vector2D::Vector2D(std::initializer_list<double> list)
{
	auto data = copy_alloc(list.begin(), list.end());
	elements = data.first;
	first_free = cap =  data.second;
}

Vector2D::Vector2D(const Vector2D& other)
{
	auto data = copy_alloc(other.elements, other.first_free);
	elements = data.first;
	first_free = cap = data.second;
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
	// TODO: insert return statement here
	free_alloc();
	auto data = copy_alloc(other.elements, other.first_free);
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void Vector2D::push_back(const double& number)
{
	check_alloc();
	alloc.construct(first_free++, number);
}
