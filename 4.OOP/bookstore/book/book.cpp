#include "book.h"

void Book::init(std::string id, std::string name, std::string author, std::string type, std::string language
              , int publish_year, int pages, double score, double price, int number_available){
    this->id=id;
    this->name=name;
    this->author=author;
    this->type=type;
    this->language=language;
    this->publish_year=publish_year;
    this->score=score;
    this->pages=pages;
    this->price=price;
    this->number_available=number_available;
}

void Book::book_info()
{
    std::cout << "Book " << ": " << std::endl;
    std::cout << "   ID: " << id << std::endl;
    std::cout << "   Name: " << name << std::endl;
    std::cout << "   Author: " << author << std::endl;
    std::cout << "   Type: " << type << std::endl;
    std::cout << "   Language: " << language << std::endl;
    std::cout << "   Publish Year: " << publish_year << std::endl;
    std::cout << "   Pages: " << pages << std::endl;
    std::cout << "   Price: " << price << std::endl;
    std::cout << "   Number Available: " << number_available << std::endl;
}

void Book::book_info_short()
{
    std::cout << id << " - " << price << " - " << number_available << " | \"" << name << "\" - " << author << std::endl;
}

std::string Book::get_type()
{
    return type;
}

std::string Book::get_language()
{
    return language;
}

std::string Book::get_id()
{
    return id;
}

std::string Book::get_name()
{
    return name;
}

std::string Book::get_author()
{
    return author;
}

double Book::get_price()
{
    return price;
}

int Book::get_number()
{
    return number_available;
}

void Book::set_number(int number)
{
    this->number_available = number;
}

int Book::get_pages()
{
    return pages;
}

double Book::get_score()
{
    return score;
}

int Book::get_publish_year()
{
    return publish_year;
}

void Book::init()
{
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << std::endl;

    std::cout << "Author: ";
    std::getline(std::cin, author);
    std::cout << std::endl;

    std::cout << "Type: ";
    std::getline(std::cin, type);
    std::cout << std::endl;

    std::cout << "Language: ";
    std::getline(std::cin, language);
    std::cout << std::endl;

    std::cout << "Publish year: ";
    std::string year;
    std::getline(std::cin, year);
    publish_year = std::stoi(year);
    std::cout << std::endl;

    std::cout << "Pages: ";
    std::string pages_;
    std::getline(std::cin, pages_);
    pages = std::stoi(pages_);
    std::cout << std::endl;

    std::cout << "Score: ";
    std::string score_;
    std::getline(std::cin, score_);
    score = std::stod(score_);
    std::cout << std::endl;
}