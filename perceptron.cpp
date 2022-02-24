#include<iostream>
#include<vector>
#include<math.h>
#include "./header/LinearAlgebra.hpp"
#include "./header/Plot.hpp"

int AND(int x1, int x2);
int NAND(int x1, int x2);
int OR(int x1, int x2);
int XOR(int x1, int x2);

int main(void){
   std::vector<float> check_AND(4);
   check_AND[0] = AND(0, 0); // 0 0 : 0
   check_AND[1] = AND(0, 1); // 0 1 : 0
   check_AND[2] = AND(1, 0); // 1 0 : 0
   check_AND[3] = AND(1, 1); // 1 1 : 0
   LinearAlgebra::Vector check_AND_vec(check_AND);
   check_AND_vec.show();

   std::vector<float> check_NAND(4);
   check_NAND[0] = NAND(0, 0); // 0 0 : 1
   check_NAND[1] = NAND(0, 1); // 0 1 : 1
   check_NAND[2] = NAND(1, 0); // 1 0 : 1
   check_NAND[3] = NAND(1, 1); // 1 1 : 0
   LinearAlgebra::Vector check_NAND_vec(check_NAND);
   check_NAND_vec.show();

   std::vector<float> check_OR(4);
   check_OR[0] = OR(0, 0);  // 0 0 : 0
   check_OR[1] = OR(0, 1);  // 0 1 : 1
   check_OR[2] = OR(1, 0);  // 1 0 : 1
   check_OR[3] = OR(1, 1);  // 1 1 : 1
   LinearAlgebra::Vector check_OR_vec(check_OR);
   check_OR_vec.show();

   std::vector<float> check_XOR(4);
   check_XOR[0] = XOR(0, 0); // 0 0 : 0
   check_XOR[1] = XOR(0, 1); // 0 1 : 1
   check_XOR[2] = XOR(1, 0); // 1 0 : 1
   check_XOR[3] = XOR(1, 1); // 1 1 : 0
   LinearAlgebra::Vector check_XOR_vec(check_XOR);
   check_XOR_vec.show();
}

int AND(int x1, int x2){
    LinearAlgebra::Vector x({(float)x1, (float)x2});
    LinearAlgebra::Vector w({0.5, 0.5});
    float b = -0.7;
    float tmp = (w * x).sum() + b;
    if(tmp <= 0) return 0;
    else return 1;
}

int NAND(int x1, int x2){
    LinearAlgebra::Vector x({(float)x1, (float)x2});
    LinearAlgebra::Vector w({-0.5, -0.5});
    float b = 0.7;
    float tmp = (w * x).sum() + b;
    if(tmp <= 0) return 0;
    else return 1;
}

int OR(int x1, int x2){
    LinearAlgebra::Vector x({(float)x1, (float)x2});
    LinearAlgebra::Vector w({0.5, 0.5});
    float b = -0.2;
    float tmp = (w * x).sum() + b;
    if(tmp <= 0) return 0;
    else return 1;
}

int XOR(int x1, int x2){
    int s1 = NAND(x1, x2);
    int s2 = OR(x1, x2);
    int y = AND(s1, s2);
    return y;
}