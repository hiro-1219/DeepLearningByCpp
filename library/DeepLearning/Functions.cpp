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

    LinearAlgebra::Matrix sigmoid(LinearAlgebra::Matrix x){
        LinearAlgebra::Vector tmp_vec = x.matrix_to_vec();
        LinearAlgebra::Vector ret_vec = sigmoid(tmp_vec);
        return ret_vec.vec_to_matrix(0);
    }

    LinearAlgebra::Vector identity_function(LinearAlgebra::Vector x){
        return x;
    }

    LinearAlgebra::Matrix identity_function(LinearAlgebra::Matrix x){
        return x;
    }


    LinearAlgebra::Vector step_function(LinearAlgebra::Vector x){
        LinearAlgebra::Vector ret_vec;
        ret_vec = x.map([](float x)->float{return x > 0;});
        return ret_vec;
    }

    LinearAlgebra::Vector ReLU(LinearAlgebra::Vector x){
        LinearAlgebra::Vector ret_vec;
        ret_vec = LinearAlgebra::maximum(LinearAlgebra::zeros(x.size), x);
        return ret_vec;
    }
}
