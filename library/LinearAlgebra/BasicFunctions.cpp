#include<iostream>
#include<vector>
#include<cmath>
#include "../../header/LinearAlgebra.hpp"

namespace LinearAlgebra::BasicFunctions{
    LinearAlgebra::Vector log(LinearAlgebra::Vector x){
        LinearAlgebra::Vector ret_vec = x.map([](float i)->float{return std::log(i);});
        return ret_vec;
    }
}