#include<iostream>
#include<vector>
#include<math.h>
#include "./header/LinearAlgebra.hpp"
#include "./header/Plot.hpp"

int AND(int x1, int x2);

int main(void){
   std::vector<float> check(4);
   check[0] = AND(0, 0); // 0 0 : 0
   check[1] = AND(0, 1); // 0 1 : 0
   check[2] = AND(1, 0); // 1 0 : 0
   check[3] = AND(1, 1); // 1 1 : 0
   LinearAlgebra::Vector check_vec(check);
   check_vec.show();
}

int AND(int x1, int x2){
    LinearAlgebra::Vector x({(float)x1, (float)x2});
    LinearAlgebra::Vector w({0.5, 0.5});
    float b = -0.7;
    float tmp = (w * x).sum() + b;
    if(tmp <= 0) return 0;
    else return 1;
}