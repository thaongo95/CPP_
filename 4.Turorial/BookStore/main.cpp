#include "BookStore.h"
#include "Book.h"
#include "Item.h"

int main(){
    BookStore store;
    Book book(1, "The Great Gatsby", "A novel by F. Scott Fitzgerald", 10, 15.99, "F. Scott Fitzgerald", "Scribner", 1925);
    Item item(2, "Generic Item", "A generic item", 5, 9.99);
    store.addItem(std::make_unique<Book>(book));
    store.addItem(std::make_unique<Item>(item));
    std::unique_ptr<Item> foundItem = store.findItemById(1);
    //foundItem->display();
    store.removeItem(1);
    store.displayItems();
    return 0;
}