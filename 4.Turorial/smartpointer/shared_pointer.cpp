#include <iostream>
#include <memory>
#include <vector>
#include "lib/smart_pointer.h"
#include "lib/smart_pointer.cpp"
class Tensor{
    std::vector<std::vector<double>> matrix3D;
    public:
        void init(int num, int n){
            for (int j=0;j<n;j++){
                std::vector<double> temp;
                for (int i=0; i<n; i++){     
                    temp.push_back(num);
                }
                matrix3D.push_back(temp);
            }
        }
        void print(){
            for (int j=0;j<matrix3D.size();j++){
                for (int i=0; i<matrix3D.size(); i++){
                    std::cout << matrix3D[j][i] << " ";
                }
                std::cout << std::endl;
            }
        }
};

int main(){
    std::cout << "Create some tensor by passing value and shape" << std::endl;
    std::cout << "The first one using Tensor class" << std::endl;
    Tensor tensor1;
    tensor1.init(1, 5);
    tensor1.print();
    std::cout << "The second one using shared pointer" << std::endl;
    std::shared_ptr<Tensor> p1(new Tensor);  
    std::cout << "address of shared pointer: " << p1.get() << std::endl;
    p1->init(0,10);
    p1->print();
    std::cout << "The third one sharing ownship by shared pointer" << std::endl;
    std::shared_ptr<Tensor> p2(p1);
    std::cout << "address of shared pointer: "  << p2.get() << std::endl;
    std::cout << "number of user: "  << p1.use_count() << std::endl;
    std::cout << "number of user: "  << p2.use_count() << std::endl;
    
    // p1.reset();
    // std::cout << p1.get() << std::endl;
    // std::cout << p2.get() << std::endl;
    // std::cout << p1.use_count() << std::endl;
    // std::cout << p2.use_count() << std::endl;
    
    std::shared_ptr<Tensor> p3 = std::make_shared<Tensor>(tensor1);
    std::cout << "The four one point to the first object" << std::endl;
    p3->print();
    std::cout << "address of shared pointer: " << p3.get() << std::endl;

    p3.swap(p2);
    std::cout << "The four one after swap ownship with the third one" << std::endl;
    p3->print();
    std::cout << "address of shared pointer: "  << p3.get() << std::endl;
    std::cout << "number of user: "  << p3.use_count() << std::endl;

    std::cout << "The last one is using smart pointer library to init " << std::endl;
    Smart_Pointer<Tensor> p_custom(new Tensor);
    p_custom->init(3, 5);
    p_custom->print();

    return 0;
}