#ifndef ENCAPSULE_H
#define ENCAPSULE_H
#include <string>


class Computer{
    private:
        std::string name;
        int product_year;
        int num_of_core;
        bool GPU{false};
        static int counter;
    public:
        Computer();
        Computer(std::string new_name, int year, int core_num);
        void set_name(std::string new_name);
        void set_year(int year);
        void set_core_num(int core_num, bool GPU);
        bool GPU_or_not();
        std::string get_name();
        int get_year();
        int get_core_num();
        void print();
};

#endif