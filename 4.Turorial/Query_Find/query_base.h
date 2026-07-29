#pragma once

#include "finder.h"


class QueryBase {
	
	friend class Query;
	
protected:
	virtual ~QueryBase() {}
	std::shared_ptr<std::vector<std::string>> lines{ std::make_shared<std::vector<std::string>>() };
	std::shared_ptr<std::set<size_t>> line_nums{ std::make_shared<std::set<size_t>>() };
	virtual void val(Finder& finder) = 0;
	virtual void print() = 0;
};