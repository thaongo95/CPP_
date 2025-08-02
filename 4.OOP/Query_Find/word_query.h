#pragma once

#include "query_base.h"


class WordQuery: public QueryBase {
protected:
	std::string word;
public:
	WordQuery() = default;
	WordQuery(const std::string& word);
	WordQuery(const WordQuery& query);
	void val(Finder& finder) override;
	void print() override;
};