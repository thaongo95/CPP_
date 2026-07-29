#include <iostream>
#include <string>
#include <vector>


template<int num>
char shiftLeft(const int& value){
    return (char)(value+num);
}


void changeSeries(const std::vector<char>& values, char (*func)(const int&)){
    for (auto value:values){
        std::cout << func(int(value)) << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::vector<char> series1 = {'e', 'r', 'f', '2', '5', 'f'};
    changeSeries(series1, shiftLeft<3>);
    changeSeries(series1, shiftLeft<0>);
    changeSeries(series1, shiftLeft<-1>);
    changeSeries(series1, shiftLeft<5>);
    changeSeries(series1, [](const int& value){ return (char)(value+3);});
    
}