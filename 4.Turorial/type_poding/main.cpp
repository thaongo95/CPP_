#include <iostream>

struct Vector2{
    int x,y;
};

struct Vector4{
    union 
    {
        struct{
            int x,y,z,h;
        };
        struct{
            Vector2 a,b;
        };      
    }; 
};

void PrintVector2(const Vector2& vt){
    std::cout << vt.x<< "," << vt.y<< std::endl;
}

int main(){
    int x = 10;
    float y = *(float*)(&x);
    std::cout << y << std::endl;
    float z = x;
    std::cout << z << std::endl;
    Vector2 vt1;vt1.x=10;vt1.y=12;
    Vector4 vt2;vt2.x=1;vt2.y=23;vt2.z=32;vt2.h=12;
    PrintVector2(vt1);
    PrintVector2(vt2.a);
}