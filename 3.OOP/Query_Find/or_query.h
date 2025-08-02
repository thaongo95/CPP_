#pragma once

#include "binary_query.h"
#include "query.h"

class OrQuery : public BinaryQuery {

public:
	OrQuery() = default;
	OrQuery(const Query& query1, const Query& query2);
	void val(Finder& finder) override;
	void print() override;
};