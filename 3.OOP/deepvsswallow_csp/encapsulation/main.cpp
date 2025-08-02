#include "encapsule.h"

int main(){
    Computer com1;
    com1.set_name("Dell");
    com1.set_year(2012);
    com1.set_core_num(12, 1);
    Computer com2("HP", 2023, 12), com3("asus", 2020, 8);
    com1.print();
    com2.print();
    com3.print();
}


