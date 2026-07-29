#include "shouji.h"
#include "shouji.cpp"

int main(){
    Shouji ph1;
    Shouji ph2("weihua", "old", "2000");
    Shouji ph3(ph2);
    Shouji ph4(5000, 32, 5.4);
    Shouji ph5(std::move(Shouji("Hello")));
    Shouji ph6(std::move(Shouji(8000, 64, 6.7)));
    ph1.xinxi();
    ph2.xinxi();
    ph3.xinxi();
    ph4.xinxi();
    ph5.xinxi();
    ph6.xinxi();
}