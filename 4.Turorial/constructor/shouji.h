#ifndef SHOUJI_H
#define SHOUJI_H
#include <iostream>
#include <string>


class Shouji{
    static int counting;
    std::string mingpai, xilie, pianhao;
    int rongliang, xiangsu;
    double pingmu;
public:
    Shouji();
    Shouji(std::string mingpai);
    Shouji(std::string mingpai, std::string xilie, std::string pianhao);
    Shouji(int rongliang, int xiangsu, double pingmu);
    Shouji(std::string name, std::string series, std::string num, 
           int during, int pixel, double screen);
    Shouji(const Shouji& one);
    Shouji(Shouji&& one);
    ~Shouji(){
        std::cout << "finished!" << mingpai << std::endl;
    };
    void xinxi();
};


#endif