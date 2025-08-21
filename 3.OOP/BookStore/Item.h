#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>

class Item{
public:
    Item(){}
    Item(int id, const std::string& name, const std::string& description, int quantity, double price);
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    int getQuantity() const;
    double getPrice() const;
    void setId(int id);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setQuantity(int quantity);
    void setPrice(double price);
    virtual void display() const;
    void updateQuantity(int quantity);
    void updatePrice(double price);
 
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    friend std::istream& operator>>(std::istream& is, Item& item);
private:    
    int m_id;
    std::string m_name;
    std::string m_description;
    int m_quantity;
    double m_price;
};

#endif // ITEM_H
