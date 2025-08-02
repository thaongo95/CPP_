#include "shouji.h"

int Shouji::counting=1;
Shouji::Shouji()
    : Shouji("kirin", "new", "2024", 7000, 45, 6.7)
{
    std::cout << "default is call!" << std::endl;
}
Shouji::Shouji(std::string mingpai)
     :Shouji(mingpai, "noJ", "K40")
{
    std::cout << "mingpai is called! " << std::endl;
}

Shouji::Shouji(std::string mingpai, std::string xilie, std::string pianhao)
    :Shouji(mingpai, xilie, pianhao, 7000, 42, 6.5)
{
    std::cout << "mingpai xilie pianhao is called!" << std::endl;
}

Shouji::Shouji(int rongliang, int xiangsu, double pingmu)
    :Shouji("colley", "spacial", "Z43", rongliang, xiangsu, pingmu)
{
    std::cout << "rongliang xiangsu pingmu is called!" << std::endl;
}

Shouji::Shouji(std::string name, std::string series, std::string num, int during, int pixel, double screen)
    : mingpai{name}, xilie{series}, pianhao{num}, rongliang{during}, xiangsu{pixel}, pingmu{screen}
{
    std::cout << "created one !" << std::endl;
    ++counting;
}

Shouji::Shouji(const Shouji &one)
{
    mingpai = one.mingpai;
    xilie = one.xilie;
    pianhao = one.pianhao;
    rongliang = one.rongliang;
    xiangsu = one.xiangsu;
    pingmu = one.pingmu;
}
Shouji::Shouji(Shouji &&one)
{
    mingpai = one.mingpai;
    xilie = one.xilie;
    pianhao = one.pianhao;
    rongliang = one.rongliang;
    xiangsu = one.xiangsu;
    pingmu = one.pingmu;
}

void Shouji::xinxi()
{
    std::cout << "        INFO " << counting << " : " << std::endl;
    std::cout << "             MINGPAI: " << mingpai << std::endl;
    std::cout << "             XILIE: " << xilie << std::endl;
    std::cout << "             PIANHAO: " << pianhao << std::endl;
    std::cout << "             RONGLIANG: " << rongliang << std::endl;
    std::cout << "             XIANGSU: " << xiangsu << std::endl;
    std::cout << "             PINGMU: " << pingmu << std::endl;

}


