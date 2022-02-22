#include<iostream>
#include<vector>
#include "./library/DeepCpp.hpp"

int main(void){
    DeepCpp::Vector a({1, 2, 3, 4, 5});
    DeepCpp::Vector b({5, 9, 10, 15, 16});
    DeepCpp::Vector c;
    DeepCpp::Vector d;
    DeepCpp::Vector e;
    DeepCpp::Vector f;
    a.show();
    b.show();
    c = a + b;
    d = b - a;
    e = a * b;
    f = a / b;
    c.show();
    d.show();
    e.show();
    f.show();
    return 0;
}