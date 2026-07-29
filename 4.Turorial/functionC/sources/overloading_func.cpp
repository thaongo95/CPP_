// template<typename T>
// T mul(T x, T y){
//     return x*y;
// }
// template<typename T>
// T mul(T a, T b, T c){
//     return a*b*c;
// }
#include<vector>
const int mul(const int &x, const int &y){
    return x*y;
}
const int mul(const int &x, const int &y,const int &z){
    return x*y*z;
}
double mul(double x, double y){
    return x*y;
}
double mul(double x, double y, double z){
    return x*y*z;
}
void increment(int *param){
    const int scaler=100;
    *param = *param*scaler;
}
void increment(float *param){
    const int scaler=100;
    *param = *param*scaler;
}
void increment(double *param){
    const int scaler=100;
    *param = *param*scaler;
}

struct bigandsmall{
    int big, small;
};

void compare_num(const int &x, const int &y , bigandsmall &param){
    param.big = (x>y) ? x:y;
    param.small = (x<y) ? x:y;
}

void compare_num(std::vector<int> arr, bigandsmall &param){
    param.big = arr[0];
    param.small = arr[0];
    for (int i=0; i< arr.size(); i++){
        if (arr[i]>param.big) param.big=arr[i];
        if (arr[i]<param.small) param.small=arr[i];
    }
}