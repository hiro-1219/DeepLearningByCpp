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

    LinearAlgebra::Matrix f({{1, 2, 3}, {4, 5, 6}});
    LinearAlgebra::Matrix g({{2, 3}, {5, 6}, {7, 8}});
    LinearAlgebra::Matrix l;
    f.show(); g.show();
    l = f.dot(g);
    l.show();

    LinearAlgebra::Matrix rand1({10, 10}, 0, 10);
    LinearAlgebra::Matrix rand2({10, 10}, 0, 10);
    LinearAlgebra::Matrix dot;
    rand1.show(); rand2.show();
    dot = rand1.dot(rand2);
    dot.show();
    return 0;
}