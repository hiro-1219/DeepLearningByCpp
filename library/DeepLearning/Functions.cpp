#include<iostream>
#include<vector>
#include<cmath>
#include "../../header/LinearAlgebra.hpp"
#include "../../header/DeepLearning.hpp"

namespace DeepLearning::Functions::Activation{
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

    LinearAlgebra::Vector softmax(LinearAlgebra::Vector x){
        float c = x.max()[0];
        std::cout << c << "\n";
        LinearAlgebra::Vector exp_a = x.map([&c](float i)->float{return exp(i - c);});
        return exp_a / exp_a.sum();
    }

    LinearAlgebra::Matrix softmax(LinearAlgebra::Matrix x){
        LinearAlgebra::Vector tmp_vec = x.matrix_to_vec();
        LinearAlgebra::Vector ret_vec = softmax(tmp_vec);
        return ret_vec.vec_to_matrix(0);
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

namespace DeepLearning::Functions::Loss{
    float sum_squared_loss(LinearAlgebra::Vector y, LinearAlgebra::Vector t){
        return 0.5 * ((y - t) * (y - t)).sum();
    }
    float cross_entropy_loss(LinearAlgebra::Vector y, LinearAlgebra::Vector t){
        float delta = 1e-7;
        return -1 * (t * LinearAlgebra::BasicFunctions::log(y + delta)).sum();
    }
    float cross_entropy_loss(std::vector<LinearAlgebra::Vector> y, std::vector<LinearAlgebra::Vector> t){
        float delta = 1e-7;
        float ret_loss = 0;
        for(int i = 0; i < y.size(); i++){
            ret_loss += cross_entropy_loss(y[i], t[i]);
        }
        return ret_loss / y.size();
    }
}