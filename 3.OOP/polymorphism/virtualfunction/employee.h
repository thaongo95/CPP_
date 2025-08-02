#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
#include <iostream>

class Employee{
    std::string name;
    int salary;
    public:
        virtual void raise_salary(double amount);
        virtual int get_salary();
};

class Manager: public Employee{
    int base_salary{3000};
    public:
        void raise_salary(double amount);
        int get_salary();
};
class Engineer: public Employee{
    int base_salary{2000};
    public:
        void raise_salary(double amount);
        int get_salary();
};
class Programmer: public Employee{
    int base_salary{2200};
    public:
        void raise_salary(double amount);
        int get_salary();
};
#endif