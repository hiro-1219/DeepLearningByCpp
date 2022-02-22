#include<iostream>
#include<vector>
#include "./library/DeepCpp.hpp"

int main(void){
    DeepCpp::Vector a({1, 2, 3, 4, 5});
    DeepCpp::Vector b({5, 9, 10, 15, 16});
    DeepCpp::Vector c;
    DeepCpp::Vector d;
    a.show();
    b.show();
    c = a + b;
    c.show();
    d = b - a;
    d.show();
    return 0;
}