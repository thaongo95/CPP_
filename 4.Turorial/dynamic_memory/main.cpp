#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Book {
	std::string name;
	std::string author;
	unsigned int pages;
	double price;
public:
	Book():name{""},author{""},pages{0}, price{00.00}{}
	Book(std::string name, std::string author, unsigned int pages, double price)
		: name{ name }, author{ author }, pages{ pages }, price{ price } {

	}
	~Book() { std::cout << "Detroyed ! " << name << std::endl; }
	std::string getName() { return name; }
	std::string getAuthor() { return author; }
	unsigned int getPages() { return pages; }
	double getPrice() { return price; }
};

int main() {
	std::shared_ptr<Book> book1 = std::make_shared<Book>("The Lost Sumbol", "Dan Brown", 712, 14.99);
	auto book2 = std::make_shared<Book>("Homo Deus", "Yuval Noah Harari", 512, 9.99);
	auto book3 = book2;
	book1.reset(new Book("Homo Sapiens", "Yuval Noah Harari", 512, 9.99));
	book2 = book1;
	
	
	std::cout << book1->getName() << std::endl;
	std::cout << book2->getName() << std::endl;
	std::cout << book3->getName() << std::endl;
	
}