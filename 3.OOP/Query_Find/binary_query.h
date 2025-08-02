#pragma once
#include "query_base.h"
#include "algorithm"
#include "iterator"


class BinaryQuery : public QueryBase {
protected:
	std::string word1;
	std::string word2;
public:
	virtual void print() = 0;
};