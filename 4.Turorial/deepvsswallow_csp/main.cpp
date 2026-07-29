#include "friend_class/thao.h"
#include "friend_class/thang.h"
#include "friend_class/thao.cpp"
#include "deepcopy.h"
#include "shallowcopy.h"
#include "staticmember.h"
#include "staticfunction.cpp"

int main(){

    // thao and thang class is testing of friend class skills
    Thao thao(100000);
    Thang thang(300000);
    thang.getfromthao(thao, 5000);
    friend_func(thao);
    friend_func(thang);
    Thao thao2(thao);
    thang.getfromthao(thao, 5000);
    friend_func(thao);
    friend_func(thao2); //default copy contructor
    friend_func(thang);

    //   #Copy constructor  #parameter contructor   #default contructor
    //   Two type of copy object are shallow copy and deep copy
    //   - Shallow copy is use by the default copy contructor when 
    // there are no heap section of memory(pointer)
    Shallow_Class shallow_class1(12, 14, 25);
    shallow_class1.show_class();
    Shallow_Class shallow_class2(shallow_class1); //default copy contructor
    shallow_class2.show_class();
    //   - Deep copy need to explicitly define the copy constructor
    // and assign dynamic memory as well, if required.
    Deep_Class deep_class1(12, 15.2313546, 'k');
    deep_class1.show_class();
    Deep_Class deep_class2(deep_class1);
    deep_class2.show_class();
    std::cout << "#####################" << std::endl;
    // static member
    std::cout << "Static member is the class member that every object can be use" << std::endl;
    House house(5.5, 25, 3);
    house.set_room(20);
    House house1;
    House house2;
    House house3;
    std::cout << "room number of house: " << house.get_room() << std::endl;
    std::cout << "size of house: " << house.get_size() << std::endl;
    std::cout << "high of house: " << house.get_hight() << std::endl;

    // static member function
    B6 thong;
    B6 huy("Huy");
    B6 huong("Huong");
    B6 six;
    std::cout << "people sum = " << B6::T << std::endl;
    std::cout << B6::get_current_name(thong) << std::endl; 
    std::cout << B6::get_current_name(huy) << std::endl;
}