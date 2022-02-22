#include<iostream>
#include<vector>
#include "./library/LinearAlgebra.hpp"

int main(void){
    LinearAlgebra::Vector a({1, 3, 5, 7, 9});
    LinearAlgebra::Vector b({2, 4, 6, 8, 10});
    LinearAlgebra::Vector add;
    float c;
    a.show(); b.show();
    add = a + b;
    c = a.dot(b);
    add.show();
    std::cout << c << "\n";
    return 0;
}