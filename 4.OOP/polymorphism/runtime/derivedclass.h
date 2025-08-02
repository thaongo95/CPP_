#ifndef DERIVEDCLASS_H
#define DERIVEDCLASS_H
#include "baseclass.h"

class Derived_1:public Baseclass{
    public:
        void function1();
        void function2();
};
class Derived_2:public Baseclass{
    public:
        void function1();
        void function2();
};
class Derived_3:public Baseclass{
    public:
        void function1();
        void function2();
};
class Derived_4:public Baseclass{
    public:
        void function1();
        void function2();
};

class Rectangle: public Shape{
    int width, height;
public:
    Rectangle(int width, int height);
    void get_area();
};

class Tritangle: public Shape{
    int bottom, height;
public:
    Tritangle(int bottom, int height);
    void get_area();
};

class Circle: public Shape{
    int R;
    const double Pi = 3.14;
public:
    Circle(int R);
    void get_area();
};

#endif