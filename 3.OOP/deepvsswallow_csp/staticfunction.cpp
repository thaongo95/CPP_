
#include<string>

/*
 -  independent of any object of the class
 -  can be called even if no objects of the class exits
 -  used o store information that is shared by all objects in a class
*/

class B6{
    public:
        B6(){};
        B6(std::string new_name);
        static int T;
        static std::string get_current_name(B6 &some);
        std::string name;

};

int B6::T=0;
B6::B6(std::string new_name){
    T++;
    name = new_name;
}

std::string B6::get_current_name(B6 &some){
    if (some.name != "")
        return some.name;
    else return "NoName";
}