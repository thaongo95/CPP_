#include "book/book.h"
 #include "book/book.cpp"
#include "bookshop/bookshop.h"
#include "bookshop/bookshop.cpp"
#include <vector>


int main(){
    BookShop bookshop;
    while (true){
        std::cout << "###################################" << std::endl;
        std::cout << "Welcome to My BookStore!!!" << std::endl;
        std::cout << "Who are you ? [Maintainer/Customer]" << std::endl;
        std::string user;
        std::getline(std::cin, user);
        if (user=="Matntainner"||user=="M"){
            bookshop.append_data();
        }
        else if(user=="Customer"||user=="C"){
            
            std::cout << "What you want to do?[search/top/all]" << std::endl;
            std::string your_choice;
            std::getline(std::cin, your_choice);
            if (your_choice=="search"||your_choice=="1"){
                bookshop.find_book();
            }
            else if (your_choice=="top"||your_choice=="2"){
                bookshop.get_top(5);
            }
            else if (your_choice=="all"||your_choice=="3"){
                bookshop.show_books_info();
            }
            else{            
                bookshop.purchase();
            }
        }
        else if(user=="-1")
            break;
        else{
            std::cout << "Please tell us who you are or type '-1' to quit!" << std::endl;
        }
    }
}