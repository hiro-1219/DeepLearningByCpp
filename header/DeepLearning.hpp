#ifndef DEEPLEARNING_HPP
#define DEEPLEARNING_HPP
#include<iostream>
#include<vector>
#include "LinearAlgebra.hpp"

namespace DeepLearning::Functions{
    LinearAlgebra::Vector sigmoid(LinearAlgebra::Vector x);       
    LinearAlgebra::Matrix sigmoid(LinearAlgebra::Matrix x);       // sigmoid
    LinearAlgebra::Vector identity_function(LinearAlgebra::Vector x);
    LinearAlgebra::Matrix identity_function(LinearAlgebra::Matrix x);
    LinearAlgebra::Vector step_function(LinearAlgebra::Vector x); // step
    LinearAlgebra::Vector ReLU(LinearAlgebra::Vector x);
}

#endif