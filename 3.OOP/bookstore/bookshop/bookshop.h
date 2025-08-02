#ifndef BOOKSHOP_H
#define BOOKSHOP_H
#include <vector>
#include <algorithm>
#include "../book/book.h"
class BookShop{
    std::vector<Book> books;
    std::vector<Book> top_books;

    void name_filter(std::vector<Book>& list);
    void author_filter(std::vector<Book>& list);
    void type_filter(std::vector<Book>& list);
    void language_filter(std::vector<Book>& list);
    void year_filter(std::vector<Book>& list);
    void pages_filter(std::vector<Book>& list);
    void score_filter(std::vector<Book>& list);
    void price_filter(std::vector<Book>& list);

    void update_rank(std::vector<Book>& book_list);
    void get_rank(int year, int number);
    void get_rank(std::string type, int number);

    public:
        BookShop();
        ~BookShop();
        void append_data();

        void show_books_info();

        void purchase();

        void find_book();

        void get_top(int number);

        
};



#endif