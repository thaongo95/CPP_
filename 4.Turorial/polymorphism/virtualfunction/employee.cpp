
#include "employee.h"

void Employee::raise_salary(double amount){
    std::cout << "Raise salary for everyone" << std::endl;
}

int Employee::get_salary(){
    std::cout << "Get salary of employee" << std::endl;
    return 0;
}

void Manager::raise_salary(double amount){
    base_salary *= (1+amount);
}

int Manager::get_salary(){
    return base_salary;
}

void Engineer::raise_salary(double amount){
    base_salary *= (1+ amount);
}

int Engineer::get_salary(){
    return base_salary;
}

void Programmer::raise_salary(double amount){
    base_salary *= (1+amount);
}

int Programmer::get_salary(){
    return base_salary;
}