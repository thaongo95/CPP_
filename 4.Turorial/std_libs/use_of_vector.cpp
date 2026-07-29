
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

std::vector<std::string> split_line(std::string line);

template<typename T>
bool compare_two(T x, T y){
    return x<y;
}

template<typename T>
void sorting(std::vector<T>& list){
    std::sort(list.begin(), list.end(), compare_two<T>);
}
template<typename T>
void print_list(std::vector<T> list){
    for (T val:list){
        std::cout << val << " ";
    }
}

int main(){
    std::ofstream fout;
    std::string line;
    fout.open("text.txt");
    while(fout.is_open()){
        std::getline(std::cin, line);
        if (line=="-1") break;
        fout << line << std::endl;
    }
    fout.close();
    std::ifstream fin;
    fin.open("text.txt");
    while(std::getline(fin, line)){
        std::vector<std::string> list_info = split_line(line);
        sorting(list_info);
        print_list(list_info);
        std::cout << std::endl;
    }
    std::vector<int> list_int{2,1,3,5,3,5,73,4,63,4,5,3};
    std::vector<std::string> list_string{"hh", "what", "wHich", "how", "and", "now"};
    sorting(list_int);
    sorting(list_string);
    print_list(list_int);
    print_list(list_string);

    
}


std::vector<std::string> split_line(std::string line){
    std::vector<std::string> list;
    std::string temp;
    for (auto ch:line){
        if (ch==','){
            list.push_back(temp);
            temp = "";
            
        }
        else temp += ch;
    }
    list.push_back(temp);
    return list;
}