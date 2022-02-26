#include<iostream>
#include<vector>
#include<math.h>
#include<map>
#include "./header/LinearAlgebra.hpp"
#include "./header/Plot.hpp"
#include "./header/DeepLearning.hpp"
using namespace DeepLearning;

std::map<std::string, LinearAlgebra::Matrix> init_network(){
    std::map<std::string, LinearAlgebra::Matrix> network;
    network["W1"] = LinearAlgebra::array({{0.1, 0.3, 0.5}, {0.2, 0.4, 0.6}});
    network["B1"] = LinearAlgebra::array({0.1, 0.2, 0.3}).vec_to_matrix(0);
    network["W2"] = LinearAlgebra::array({{0.1, 0.4}, {0.2, 0.5}, {0.3, 0.6}});
    network["B2"] = LinearAlgebra::array({0.1, 0.2}).vec_to_matrix(0);
    network["W3"] = LinearAlgebra::array({{0.1, 0.3}, {0.2, 0.4}});
    network["B3"] = LinearAlgebra::array({0.1, 0.2}).vec_to_matrix(0);
    return network;
}

LinearAlgebra::Vector forward(std::map<std::string, LinearAlgebra::Matrix> network, LinearAlgebra::Vector x){
    LinearAlgebra::Matrix W1 = network["W1"];
    LinearAlgebra::Matrix W2 = network["W2"];
    LinearAlgebra::Matrix W3 = network["W3"];
    LinearAlgebra::Matrix B1 = network["B1"];
    LinearAlgebra::Matrix B2 = network["B2"];
    LinearAlgebra::Matrix B3 = network["B3"];
    LinearAlgebra::Matrix X = x.vec_to_matrix(0);

    LinearAlgebra::Matrix A1 = X.dot(W1) + B1;
    LinearAlgebra::Matrix Z1 = Functions::Activation::sigmoid(A1);
    LinearAlgebra::Matrix A2 = Z1.dot(W2) + B2;
    LinearAlgebra::Matrix Z2 = Functions::Activation::sigmoid(A2);
    LinearAlgebra::Matrix A3 = Z2.dot(W3) + B3;
    LinearAlgebra::Matrix y = Functions::Activation::identity_function(A3);

    return y.matrix_to_vec();
}

int main(void){
    std::map<std::string, LinearAlgebra::Matrix> network = init_network();
    LinearAlgebra::Vector x({1.0, 0.5});
    LinearAlgebra::Vector y = forward(network, x);
    y.show();
    return 0;
}