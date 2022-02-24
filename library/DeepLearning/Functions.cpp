#include<iostream>
#include<vector>
#include<math.h>
#include "../../header/LinearAlgebra.hpp"
#include "../../header/DeepLearning.hpp"

namespace DeepLearning::Functions{
    LinearAlgebra::Vector sigmoid(LinearAlgebra::Vector x){
        LinearAlgebra::Vector ret_vec;
        ret_vec = x.map([](float x)->float{return 1 / (1 + exp(-x));});
        return ret_vec;
    }

    LinearAlgebra::Vector step_function(LinearAlgebra::Vector x){
        LinearAlgebra::Vector ret_vec;
        ret_vec = x.map([](float x)->float{return x > 0;});
        return ret_vec;
    }
}
