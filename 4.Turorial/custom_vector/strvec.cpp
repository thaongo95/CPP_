#include "strvec.h"

std::allocator<std::string> StrVec::alloc;

std::pair<std::string*, std::string*> StrVec::alloc_n_copy(const std::string* begin, const std::string* end)
{
	auto data = alloc.allocate(end - begin);
	return { data, std::uninitialized_copy(begin, end, data) };
}

void StrVec::free()
{
	if (elements) {
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i) {
		alloc.construct(dest++, std::move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

StrVec::StrVec(std::initializer_list<std::string> list)
{
	auto newdata = alloc_n_copy(list.begin(), list.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(const StrVec& other)
{
	auto newdata = alloc_n_copy(other.begin(), other.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec&& other) noexcept :
	elements(other.elements), first_free(other.first_free), cap(other.cap)
{
	other.elements = other.first_free = other.cap = nullptr;
}

StrVec& StrVec::operator=(const StrVec& other)
{
	// TODO: insert return statement here
	auto data = alloc_n_copy(other.begin(), other.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec& StrVec::operator=(StrVec&& other) noexcept
{
	// TODO: insert return statement here
	if (this != &other) {
		free();
		elements = other.elements;
		first_free = other.first_free;
		cap = other.cap;
		other.elements = other.first_free = other.cap = nullptr;
	}
	return *this;
}

StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const std::string& str)
{
	check_n_alloc();
	alloc.construct(first_free++, str);
	std::cout << "using lvalue" << std::endl;
}

void StrVec::push_back(std::string&& str)
{
	check_n_alloc();
	alloc.construct(first_free++, std::move(str));
	std::cout << "using rvalue" << std::endl;
}
