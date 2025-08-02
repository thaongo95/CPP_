#include "query.h"
#include "finder.h"

int main() {
	Finder finder("input.txt");
	Query query("as");
	query.val(finder);
	Query query1 = Query("they") | Query("as");
	query1.val(finder);
	query1.print_info();

}