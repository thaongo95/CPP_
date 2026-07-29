#pragma once
#include <iostream>
/*
   Smart Pointer is a wrapper class over a pointer with an operator like * and -> overload
   the object of the smart pointer class look lik normal pointer
   but it can dealllocate and free destroyed object memory.
    https://www.geeksforgeeks.org/smart-pointers-cpp/
*/
template<typename T>
class Smart_Pointer{
    T *ptr;
    static int count;
public:
    explicit Smart_Pointer(T* p=NULL);
    ~Smart_Pointer();
    T& operator*();
    T* operator->();
};

