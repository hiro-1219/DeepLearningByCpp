#ifndef DEEPLEARNING_HPP
#define DEEPLEARNING_HPP
#include<iostream>
#include<vector>
#include "LinearAlgebra.hpp"

namespace DeepLearning::Functions{
    LinearAlgebra::Vector sigmoid(LinearAlgebra::Vector x);       // sigmoid
    LinearAlgebra::Vector step_function(LinearAlgebra::Vector x); // step
}

#endif