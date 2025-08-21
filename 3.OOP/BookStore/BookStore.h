#include "Item.h"
#include <vector>
#include <memory>

class BookStore {
    friend Item;
public:
    void addItem(std::unique_ptr<Item> item);
    void removeItem(int id);
    void displayItems() const;
    std::unique_ptr<Item> findItemById(int id);
private:
    std::vector<std::unique_ptr<Item>> m_items;     
};