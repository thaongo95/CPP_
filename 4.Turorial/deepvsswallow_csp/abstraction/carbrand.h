#ifndef CARBRAND_H
#define CARBRAND_H

#include <string>
#include <vector>
#include <iostream>

/*
    Abstraction refers to the concept of hiding the complex implemnetation 
    details and showing only the essential features of an object.
    Encapsulation, on the other hand, involves bundling the data and methods
    that operate on the data and methos that restricting access to some of the
    object's components. 
    So, abstraction focuses on the outside view of an object, while encapsulation 
    focuses on the internal organization of an object 
*/

class Carbrand{
    std::vector<std::string> honda = {"CRV", "HRV", "BRV", "Civic", "City", "Bio", "Accord"};
    std::vector<std::string> hyundai = {"Santafe", "Creta", "Accent", "Tusson", "Grand i10" ,"Kona", "Venue", "Elantra", "Palisade"};
    std::vector<std::string> kia = {"Sportage", "Sorento", "Carens", "Seltos", "Sonets", "K3", "K5", "Morning", "Soluto"};
    std::vector<std::string> ford = {"Everest", "Range", "Ecosport", "Territory", "Focus", "Transit", "Mustang"};
    std::vector<std::string> toyota = {"Fortuner", "Land Cruiser", "Innova", "Raize", "Camry", "Wigo", "Yaris"};
    std::string brand_name;
    public:
        Carbrand(){};
        Carbrand(std::string brand_name);
        int get_number_of_cars();
        void get_all_type_of_car();
};

/*
   the abstraction is hiding all the variable inside the class
   when the encapsule is access the variable via methods getter and setter
*/

#endif