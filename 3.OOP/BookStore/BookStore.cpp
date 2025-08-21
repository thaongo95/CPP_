#include "BookStore.h"
#include <algorithm>


void BookStore::addItem(std::unique_ptr<Item> item)
{
    m_items.push_back(std::move(item));
}

void BookStore::removeItem(int id)
{
    auto it = std::remove_if(m_items.begin(), m_items.end(), [id](const std::unique_ptr<Item>& item) { return item->getId() == id; });
    m_items.erase(it, m_items.end());
}

void BookStore::displayItems() const
{
    for (const auto &item : m_items)
    {
        item->display();
        std::cout << "------------------------\n";
    }
}

std::unique_ptr<Item> BookStore::findItemById(int id)
{
    for (auto &item : m_items)
    {
        if (item->getId() == id)
        {
            std::cout << "Item found: \n";
            item->display();
            std::cout << "------------------------\n";
            return std::make_unique<Item>(*item);
        }
    }
    std::cout << "Item not found.\n";
    return nullptr;
}
