#include<iostream>

enum Month{
    January = 1,
    February = 2,
    March =3,
    April =4,
    May =5,
    June =6,
    July =7,
    August =8,
    September =9,
    October =10,
    November =11, 
    December = 12
};
enum rainbow{
    violet,
    indigo,
    blue,
    green,yellow,orange,red
}colors;

int main(){
    enum Month month;
    std::cout << January << " " << July << std::endl;
    std::cout << orange << " " << yellow << "" << violet << std::endl;
}