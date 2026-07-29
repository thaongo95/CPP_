#ifndef STATICMEMBER_H
#define STATICMEMBER_H
#include <string>

/*
  - Only one copy of that member is created for the entire class
   and is shared by all the objects of that class, no matter how
   many objects are created.
  - It is initialized before any object of this class is created
  , even before the main starts.
  - It is visible only within the class, but its lifetime is the
   entire program.
*/
class House
{
    const double floor_high{3.5};
    static int counter; // the static keyword use to declared that variable memory can not be change.
private:
    double width, height, length;
    int floor_num, room_num;
    std::string color; 
public:
    House();
    House(double new_width, double new_length, int new_floor_num);
    House(House &other_house);
    double get_size();
    double get_hight();
    void set_color(std::string new_color);
    void set_room(double room);
    int get_room();
};
int House::counter=0;
House::House(){
    std::cout << "Object number : " << ++counter << std::endl;   
}
House::House(double new_width, double new_length, int new_floor_num){
    width = new_width;
    length = new_length;
    floor_num = new_floor_num;
    std::cout << "Object number : " << ++counter << std::endl; 
}
House::House(House &other_house){
    width = other_house.width;
    length = other_house.length;
    floor_num = other_house.floor_num;
    std::cout << "Object number : " << ++counter << std::endl; 
}

double House::get_size(){
    return width*length*floor_high;
}

double House::get_hight(){
    height = floor_num*floor_high;
    return height;
}

void House::set_color(std::string new_color){
    color = new_color;
}
void House::set_room(double room){
    room_num = int(get_size()/room);
}

int House::get_room(){
    return room_num;
}

#endif