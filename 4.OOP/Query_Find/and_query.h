#pragma once
#include "binary_query.h"
#include "query.h"

class Query;

class AndQuery : public BinaryQuery {
public:
	AndQuery() = default;
	AndQuery(const Query& query1, const Query& query2);
	void val(Finder& finder) override;
	void print() override;
};