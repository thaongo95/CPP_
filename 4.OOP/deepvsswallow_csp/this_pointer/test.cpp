/*
  1) each object gets it own coopy of the data member.
  2) all-access the same function definition as present in the code segment
  --> this pointer is passed as a hidden argument to all nonstatic member function
      calls and is available as a local variable within the body of all nonstatic functions
*/
// this could be the reference than the pointer
#include<iostream>

class Test{
    private:
        int x,y;
    public:
        Test(int x=0, int y=0){
            this->x = x;
            this->y = y;
        }
        Test &setX(int new_x){
            x = new_x;
            return *this;
        }
        Test &setY(int new_y){
            y = new_y;
            return *this;
        }
        void print(){
            std::cout << "x = " << x << " y = " << y << std::endl;
        }
};

int main(){
    Test obj1(5, 5);
    obj1.setX(7).setY(10);
    obj1.print();
}