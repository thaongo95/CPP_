#ifndef BOOK_H
#define BOOK_H

#include "Item.h"

class Book : public Item {
public:
    Book() {}
    Book(int id, const std::string &name, const std::string &description, int quantity, double price, const std::string &author, const std::string &publisher, int publicationYear)
        : Item(id, name, description, quantity, price), m_author(author), m_publisher(publisher), m_publicationYear(publicationYear) {}

    std::string getAuthor() const { return m_author; }
    std::string getPublisher() const { return m_publisher; }
    int getPublicationYear() const { return m_publicationYear; }

    void setAuthor(const std::string &author) { m_author = author; }
    void setPublisher(const std::string &publisher) { m_publisher = publisher; }
    void setPublicationYear(int year) { m_publicationYear = year; }

    void display() const override {
        Item::display();
        std::cout << "Author: " << m_author << "\n"
                  << "Publisher: " << m_publisher << "\n"
                  << "Publication Year: " << m_publicationYear << "\n";
    }
private:
    std::string m_author;
    std::string m_publisher;
    int m_publicationYear;};

#endif