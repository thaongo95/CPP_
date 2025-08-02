#ifndef QUERY_H
#define QUERY_H
#pragma once
#include "query_base.h"
#include "word_query.h"
#include "not_query.h"
#include "and_query.h"
#include "or_query.h"

class Query {
	std::shared_ptr<QueryBase> ptr;
	Query(std::shared_ptr<QueryBase> query);
protected:

	friend Query operator!(const Query& query);
	friend Query operator&(const Query& query1, const Query& query2);
	friend Query operator|(const Query& query1, const Query& query2);

public:
	std::string word;
	Query(const std::string& word);
	Query(const Query& query);
	void val(Finder& finder) const;
	void print_info() const;
	
};

#endif