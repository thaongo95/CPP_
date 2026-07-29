#include <iostream>
#include <chrono>
#include <thread>


using namespace std::literals::chrono_literals;


class Timer{
    std::chrono::high_resolution_clock::time_point start,end;
    std::chrono::duration<float> duration_;
    public:
        Timer (){
            start = std::chrono::high_resolution_clock::now();
        }
        ~Timer(){
            end = std::chrono::high_resolution_clock::now();
            duration_ = end - start;
            float ms = duration_.count() * 1000.00f;
            std::cout << "Finished in " << ms << "ms" << std::endl;
        }
};

void print_loop(){
    Timer timer;
    for (int i{0}; i<1000; i++){
        for (int j{0}; j<1000; j++){
            std::cout << "[" << i << "," << j << "]" << std::endl;
        }      
    }
}

int main(){
    print_loop();
}