#include <iostream>
#include <thread>
#include <chrono>

static bool flag1{false};
static bool flag2{false};
static bool flag3{false};
static bool flag4{false};

using namespace std::literals::chrono_literals;

void thread_1(){
    while(!flag1){
        std::cout << "THREAD [" << std::this_thread::get_id() << "] is working ... " << std::endl;
        std::this_thread::sleep_for(0.3s);
    }
    
}
void thread_2(){
    while(!flag2){
        std::cout << "THREAD [" << std::this_thread::get_id() << "] is working ... " << std::endl;
        std::this_thread::sleep_for(0.5s);
    }
    
}
void thread_3(){
    while(!flag3){
        std::cout << "THREAD [" << std::this_thread::get_id() << "] is working ... " << std::endl;
        std::this_thread::sleep_for(0.7s);
    }
    
}
void thread_4(){
    while(!flag4){
        std::cout << "THREAD [" << std::this_thread::get_id() << "] is working ... " << std::endl;
        std::this_thread::sleep_for(0.9s);
    }
    
}

int main(){
    std::thread th1(thread_1), th2(thread_2), th3(thread_3), th4(thread_4);
    auto start = std::chrono::high_resolution_clock::now();
    std::cin.get();
    flag1=true;
    std::cin.get();
    flag3=true;
    std::cin.get();
    flag2=true;
    std::cin.get();
    flag4=true;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration_ = end-start;
    std::cout << "Finished in " << duration_.count() << "s" << std::endl;
    th1.join();th2.join();th3.join();th4.join();
}