#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Sales_item{
public:
    int x;
    std::string isbn;
};

int main()
{
    Sales_item item1, item2;
    cin >> item1.isbn >> item2.isbn;
    // first check that item1 and item2 represent the same book
    try{
        if (item1.isbn != item2.isbn) {
        cout << item1.isbn  + item2.isbn << endl;
        
        } else throw runtime_error("Data must refer to same ISBN");
    }
    catch(runtime_error& err){
        cout << err.what() << endl;
    }
    
}