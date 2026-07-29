#ifndef NOT_QUERY_H
#define NOT_QUERY_H
#pragma once
#include "word_query.h"
#include "query.h"

class Query;
class NotQuery : public WordQuery {
	std::shared_ptr<std::set<size_t>> not_line_nums = std::make_shared<std::set<size_t >>();
public:
	NotQuery(const Query& query);
	void val(Finder& finder) override;
	void print() override;
};

#endif