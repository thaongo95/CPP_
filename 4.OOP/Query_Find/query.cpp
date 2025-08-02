#include "query.h"

Query::Query(const std::string& word) :
	word{ word },
	ptr{ std::make_shared<WordQuery>(word) }
{
}

Query::Query(const Query& query):
	ptr{query.ptr},
	word{query.word}
{
}
void Query::val(Finder& finder) const
{
	ptr->val(finder);
}

Query::Query(std::shared_ptr<QueryBase> query):
	ptr{query}
{
}


void Query::print_info() const
{
	ptr->print();
}

Query operator!(const Query& query)
{
	auto new_ptr = std::make_shared<NotQuery>(query);
	return Query(new_ptr);
}


Query operator&(const Query& query1, const Query& query2)
{
	auto new_ptr = std::make_shared<AndQuery>(query1, query2);
	return Query(new_ptr);
}

Query operator|(const Query& query1, const Query& query2)
{
	auto new_ptr = std::make_shared<OrQuery>(query1, query2);
	return  Query(new_ptr);
}
