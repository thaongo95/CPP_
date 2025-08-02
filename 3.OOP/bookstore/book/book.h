#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>

class Book{
private:
    std::string id;
    std::string name;
    std::string author;
    int pages{0};
    std::string type;
    std::string language;
    int publish_year{0};
    double score{0};
    int rank{0};
    double price{0};
    int number_available{0};

public:
    Book(){};
    ~Book(){};
    void init(std::string id, std::string name, std::string author, std::string type, std::string language
              , int publish_year, int pages, double score, double price, int number_available);
    void init();
    void book_info();
    void book_info_short();
    std::string get_id();
    std::string get_name();
    std::string get_author();
    std::string get_type();
    std::string get_language();
    int get_publish_year();
    int get_pages();
    double get_score();
    double get_price();
    int get_number();

    void set_number(int number);
      
};


#endif