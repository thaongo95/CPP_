/*
    templates are expanded at compiler time, like macros.
    the difference is, that the compiler does type-checking before
    template expansion. The idea is simple, source  code contains 
    only function/class, but compiled code may contain multiple 
    copies of the same function/class.
*/
#include <iostream>

template<typename A>
class Arr{
    int num;
    A* value;
    public:
        Arr(A _value[], int _num);
        void print();

};

template<typename A> Arr<A>::Arr(A _value[], int _num){
    value = new A;
    num = _num;
    for (int i=0; i<num ; i++)
        *(value+i) = _value[i];
}

template<typename A> void Arr<A>::print(){
    for (int i=0; i<num ; i++)
        std::cout << " " << *(value+i);
    std::cout << std::endl;
}

int main(){
    int list[5] = {12, 13, 23, 23, 21};
    Arr<int> arr(list, 5);  
    arr.print();
}

/*
   When you use a template functio or class in C++, the compiler generates multiple
   copies of that function for each type you instantiate it with. If you instantiate 
   the template funciton with a class type that you're created, the complier will generate
   a separate copy of that class type that you use with the template. This is known as template 
   instantiation
*/