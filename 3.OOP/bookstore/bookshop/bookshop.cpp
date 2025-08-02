#include "bookshop.h"
#include <fstream>
#include <iomanip>
#include <iostream>

Book get_book_from_line(std::string line){
    Book book;
    std::vector<std::string> features;
    std::string temp;
    for (int i{0}; i<line.size(); i++){
        if (line[i]=='-'){
            features.push_back(temp);
            temp = "";
        }
        else{
            temp+=line[i];
        } 
    }
    book.init(features[0],features[1],features[2],features[3],features[4],
              std::stoi(features[5]),std::stoi(features[6]),std::stod(features[7]),
              std::stod(features[8]),std::stoi(temp));
    return book;
}

BookShop::BookShop()
{
    // bookstore load data from the bookstore.txt file
    std::ifstream fin;
    std::string line;
    fin.open("bookstore.txt");
    while (std::getline(fin, line)){
        Book book;
        book = get_book_from_line(line);
        books.push_back(book);
    }
    fin.close();
    
}

BookShop::~BookShop()
{ 
    // save bookstore into bookstore.txt while exit the BookShop class
    // because the number available of books is change by purchase so all data is rewrited
    std::ofstream fout;
    std::string line;
    fout.open("bookstore.txt");
    for (int i{0}; i<books.size();i++){
        line = books[i].get_id() + "-" + books[i].get_name() + "-" + 
            books[i].get_author() + "-" + books[i].get_type() + "-" +
            books[i].get_language() + "-" + std::to_string(books[i].get_publish_year())
             + "-" + std::to_string(books[i].get_pages()) + "-" + std::to_string(books[i].get_score())
             + "-" + std::to_string(books[i].get_price()) + "-" + std::to_string(books[i].get_number());
        fout << line << std::endl;
    }
    fout.close();
}

void BookShop::show_books_info()
{
    for (int i{0}; i<books.size(); i++){
        //books[i].book_info(); 
        books[i].book_info_short(); 
    }
    purchase();
}

/*

*********************************************APPEND BOOKS***************************************

*/



void BookShop::append_data()
{
    std::ofstream fout;
    std::string line;
    std::cout << "Input Format: NAME-AUTHOR-TYPE-LANGUAGE-YEAR-PAGES-SCORE-PRICE-NUMBERS"<< std::endl;
    fout.open("bookstore.txt", std::ios::app);   //app is append
    while (fout){
        std::getline(std::cin, line);
        std::string id_calculated;
        id_calculated += line[0];
        for (int i=0; i< line.size(); i++){
            if ((line[i]=='-')&&(id_calculated.size()<8)){
                id_calculated+= line[i+1];
            }
        }
        if (line=="-1")
            break;
        fout << id_calculated + "-" +line << std::endl;
        Book book;
        book = get_book_from_line(id_calculated + "-" +line);
        books.push_back(book);
    }
    fout.close();
}


/*

**********************************************PURCHASE*********************************************

*/

void BookShop::purchase()
{
    std::vector<Book*> waiting_list;
    std::vector<int> purchase_number;
    double total_price{0};
    while(true){
        std::string book_id, number;
        bool id_invalid{true};
        std::cout << "Input the ID of the books you want to buy: " << std::endl;
        std::getline(std::cin, book_id);
        if (book_id=="-1") break;
        for (int i{0}; i<books.size(); i++){
            if (book_id==books[i].get_id()){
                id_invalid=false;
                waiting_list.push_back(&books[i]);
                std::cout << "This book has " << books[i].get_number() << " available" << std::endl;
            }
        }
        if (id_invalid){
            std::cout << "The ID is invalid" << std::endl;
            continue;
        }
        
        std::cout << "How many copies of this book you want to buy:" << std::endl;
        std::getline(std::cin, number);
        if (number=="-1") break;
        Book * book_temp = waiting_list[waiting_list.size()-1];
        if (std::stoi(number) > book_temp->get_number()){
            std::cout << "out of stock" << std::endl;
            waiting_list.pop_back();
        }
        else {
            purchase_number.push_back(std::stoi(number));
        }
        std::string flag;
        std::cout << "do you want to continue ?" << std::endl;
        std::getline(std::cin, flag);
        if(flag != "yes")
            break;
    }
    std::cout << "########################################################" << std::endl;
    std::cout << "########################################################" << std::endl;
    std::cout << "You selected " << waiting_list.size() << " books" << std::endl;
    for (int i{0}; i<waiting_list.size(); i++){
        std::cout << "   " << i << ". " << waiting_list[i]->get_name() << "  " << purchase_number[i] 
                  << "   " <<  purchase_number[i]*waiting_list[i]->get_price() << std::endl;
        total_price += purchase_number[i]*waiting_list[i]->get_price();
    }
    std::cout << "    Total Price: " << total_price << std::endl;

    std::string purchase_flag;
    std::cout << "do you want to purchase ?" << std::endl;
    std::getline(std::cin, purchase_flag);
    if (purchase_flag=="yes"){
        for (int i{0}; i<waiting_list.size(); i++){
            waiting_list[i]->set_number(waiting_list[i]->get_number()-purchase_number[i]);
        }
        std::cout << "Purchase Completed!" << std::endl;
    }
    else {
        std::cout << "Purchase Failed!" << std::endl;
    }

}

/*

******************************FIND BOOK********************************

*/


void BookShop::find_book()
{
    std::cout << "Filter: ? [name/author/type/language/year/pages/score/price]" << std::endl;
    std::vector<Book> list_filtered;
    std::string filter;
    std::getline(std::cin, filter);
    if (filter=="name"||filter=="1"){
        name_filter(list_filtered);
    }   
    else if (filter=="author"||filter=="2"){
        author_filter(list_filtered);
    } 
    else if (filter=="type"||filter=="3"){
        type_filter(list_filtered);
    }
    else if (filter=="language"||filter=="4"){
        language_filter(list_filtered);
    }
    else if (filter=="year"||filter=="5"){
        year_filter(list_filtered);
    }
    else if (filter=="pages"||filter=="6"){
        pages_filter(list_filtered);
    }
    else if (filter=="score"||filter=="7"){
        score_filter(list_filtered);
    }
    else if (filter=="price"||filter=="8"){
        price_filter(list_filtered);
    }
    else {
        std::cout << "Please input one of the filters suggested above and try again" << std::endl;
    }
    if (list_filtered.size()!=0){
        std::cout << "Results: " << std::endl;
        for (Book book:list_filtered){
            book.book_info_short();
        }
    }
    purchase();
}


void BookShop::name_filter(std::vector<Book> &list)
{
    std::string nameInput;
    std::cout << "Input Name of the book you want to find: "<< std::endl;
    std::getline(std::cin, nameInput);
    for (auto book:books){
        size_t found = book.get_name().find(nameInput);
        if (found!= std::string::npos){
            list.push_back(book);
        }
    }
}

void BookShop::author_filter(std::vector<Book> &list)
{
    std::string authorInput;
    std::cout << "Input Name of the author you want to find: "<< std::endl;
    std::getline(std::cin, authorInput);
    for (auto book:books){
        size_t found = book.get_author().find(authorInput);
        if (found!= std::string::npos){
            list.push_back(book);
        }
    }
}

void BookShop::type_filter(std::vector<Book> &list)
{
    std::string typeInput;
    std::cout << "Input Name of the type you want to find: "<< std::endl;
    std::getline(std::cin, typeInput);
    for (auto book:books){
        size_t found = book.get_type().find(typeInput);
        if (found!= std::string::npos){
            list.push_back(book);
        }
    }
}

void BookShop::language_filter(std::vector<Book> &list)
{
    std::string languageInput;
    std::cout << "Input Name of the language you want to find: "<< std::endl;
    std::getline(std::cin, languageInput);
    for (auto book:books){
        size_t found = book.get_language().find(languageInput);
        if (found!= std::string::npos){
            list.push_back(book);
        }
    }
}

void BookShop::year_filter(std::vector<Book> &list)
{
    std::string lower_limit;
    std::string upper_limit;
    std::cout << "From: " << std::endl;
    std::getline(std::cin, lower_limit);
    std::cout << "To: " << std::endl;
    std::getline(std::cin, upper_limit);
    for (Book book:books){
        if (book.get_publish_year()<=std::stoi(upper_limit)
            &&
            book.get_publish_year()>=std::stoi(lower_limit))
            list.push_back(book);
    }
}

void BookShop::pages_filter(std::vector<Book> &list)
{
    std::string lower_limit;
    std::string upper_limit;
    std::cout << "From: " << std::endl;
    std::getline(std::cin, lower_limit);
    std::cout << "To: " << std::endl;
    std::getline(std::cin, upper_limit);
    for (Book book:books){
        if (book.get_pages()<=std::stoi(upper_limit)
            &&
            book.get_pages()>=std::stoi(lower_limit))
            list.push_back(book);
    }
}

void BookShop::score_filter(std::vector<Book> &list)
{
    std::string lower_limit;
    std::string upper_limit;
    std::cout << "From: " << std::endl;
    std::getline(std::cin, lower_limit);
    std::cout << "To: " << std::endl;
    std::getline(std::cin, upper_limit);
    for (Book book:books){
        if (book.get_score()<=std::stod(upper_limit)
            &&
            book.get_score()>=std::stod(lower_limit))
            list.push_back(book);
    }
}

void BookShop::price_filter(std::vector<Book> &list)
{
    std::string lower_limit;
    std::string upper_limit;
    std::cout << "From: " << std::endl;
    std::getline(std::cin, lower_limit);
    std::cout << "To: " << std::endl;
    std::getline(std::cin, upper_limit);
    for (Book book:books){
        if (book.get_price()<=std::stod(upper_limit)
            &&
            book.get_price()>=std::stod(lower_limit))
            list.push_back(book);
    }
}





/*

***************************************GET TOP***********************************************

*/
void BookShop::get_top(int number)
{
    std::string filter;
    std::cout << "Filter? [year/type]" << std::endl;
    std::getline(std::cin, filter);
    if (filter=="year"||filter=="1"){
        std::string year;
        std::cout << "Input a year:" << std::endl;
        std::getline(std::cin, year);
        get_rank(std::stoi(year), number);
        std::string buy_flag;
        std::cout << "Do you want to purchase?" << std::endl;
        std::getline(std::cin, buy_flag);
        if (buy_flag=="yes") 
            purchase();
    }
    else if (filter=="type"||filter=="2"){
        std::string type;
        std::cout << "Input a type:" << std::endl;
        std::getline(std::cin, type);
        get_rank(type, number);
        std::string buy_flag;
        std::cout << "Do you want to purchase?" << std::endl;
        std::getline(std::cin, buy_flag);
        if (buy_flag=="yes") 
            purchase();
    }
    else {
        std::cout << "Invalid input" << std::endl;
    }
}

bool compare_books(Book book1, Book book2)
{
    return book1.get_score()>book2.get_score();
}

void BookShop::update_rank(std::vector<Book>& book_list)
{
    std::sort(book_list.begin(), book_list.end(), compare_books);
}

void BookShop::get_rank(int year, int number)
{
    std::vector<Book> copy_list;
    for (Book book:books){
        if (book.get_publish_year()==year){
            copy_list.push_back(book);
        }
    }
    if (copy_list.size()==0){
        std::cout << "we dont have books of this year!" << std::endl;
    }
    else{
        update_rank(copy_list);
        std::cout << "Top 5 books of the year " << year << " : " << std::endl;
        int top{number};
        if (copy_list.size()<top) top=copy_list.size();
        for (int i{0}; i< top; i++){
            std::cout << i+1 << ". " << copy_list[i].get_id() << " - "<< copy_list[i].get_name()
            << " - "<<copy_list[i].get_author() << " | " << copy_list[i].get_price() << " - "
            << copy_list[i].get_number()<< std::endl;          
        }
    }
    
}

void BookShop::get_rank(std::string type, int number)
{
    std::vector<Book> copy_list;
    for (Book book:books){
        if (book.get_type()==type){
            copy_list.push_back(book);
        }
    }
    if (copy_list.size()==0){
        std::cout << "we dont have books of this type!" << std::endl;
    }
    else{
        update_rank(copy_list);
        std::cout << "Top 5 books of the " << type << " type: " << std::endl;
        int top{number};
        if (copy_list.size()<top) top=copy_list.size();
        for (int i{0}; i< top; i++){
            std::cout << i+1 << ". " << copy_list[i].get_id() << " - "<< copy_list[i].get_name()
            << " - "<<copy_list[i].get_author() << " | " << copy_list[i].get_price() << " - "
            << copy_list[i].get_number() << std::endl;          
        }
    }
}
