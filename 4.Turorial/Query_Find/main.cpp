// main.cpp
#include "finder.h"
#include "word_query.h"
#include <iostream>

int main() {
    Finder f("input.txt");
    auto res = f.find("example"); // change to a word in your input.txt
    // print result using your Result/WordQuery classes or inspect in debugger
    std::cout << "Search finished\n";
    return 0;
}