#include "Item.h"

Item::Item(int id, const std::string &name, const std::string &description, int quantity, double price):
m_id(id), m_name(name), m_description(description), m_quantity(quantity), m_price(price)
{
    // Constructor body can be empty as member initializer list is used
}

int Item::getId() const
{
    return m_id;
}

std::string Item::getName() const
{
    return m_name;
}

std::string Item::getDescription() const
{
    return m_description;
}

int Item::getQuantity() const
{
    return m_quantity;
}

double Item::getPrice() const
{
    return m_price;
}

void Item::setId(int id)
{
    m_id = id;
}

void Item::setName(const std::string &name)
{   
    m_name = name;
}

void Item::setDescription(const std::string &description)
{
    m_description = description;
}

void Item::setQuantity(int quantity)
{
    m_quantity = quantity;
}

void Item::setPrice(double price)
{
    m_price = price;
}

void Item::display() const
{
    std::cout << "ID: " << m_id << "\n"
              << "Name: " << m_name << "\n"
              << "Description: " << m_description << "\n"
              << "Quantity: " << m_quantity << "\n"
              << "Price: $" << m_price << std::endl;
}

void Item::updateQuantity(int quantity)
{
    m_quantity += quantity;
}

void Item::updatePrice(double price)
{
    m_price = price;
}

std::ostream &operator<<(std::ostream &os, const Item &item)
{
    os  << "ID: " << item.m_id << "\n"
    << "Name: " << item.m_name << "\n"
    << "Description: " << item.m_description << "\n"
    << "Quantity: " << item.m_quantity << "\n"
    << "Price: $" << item.m_price << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Item &item)
{
    is >> item.m_id;
    is.ignore(); // Ignore the newline character after the ID
    std::getline(is, item.m_name);
    std::getline(is, item.m_description);
    is >> item.m_quantity;
    is >> item.m_price;
    return is;
}
