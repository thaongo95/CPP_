#include "smart_pointer.h"

template<typename T>
int Smart_Pointer<T>::count = 0;

template<typename T>
Smart_Pointer<T>::Smart_Pointer(T* p){
    ptr = p;
    count++;
}
template<typename T>
Smart_Pointer<T>::~Smart_Pointer(){
    count--;
    std::cout << "delete pointer" << std::endl;
    delete(ptr);
}

template<typename T>
T& Smart_Pointer<T>::operator*(){
    return *ptr;
}
template<typename T>
T* Smart_Pointer<T>::operator->(){
    return ptr;
}