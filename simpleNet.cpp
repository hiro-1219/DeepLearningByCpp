#include<iostream>
#include<vector>
#include<cmath>
#include "./header/LinearAlgebra.hpp"
#include "./header/Plot.hpp"
#include "./header/DeepLearning.hpp"
using namespace DeepLearning;

class SimpleNet : public BaseNetwork{
    public:
        LinearAlgebra::Matrix W;
        SimpleNet(){
            //W = LinearAlgebra::array_random({2, 3}, -1, 1);
            W = LinearAlgebra::array({{0.47355232, 0.9977393, 0.84668094}, {0.85557411, 0.03563661, 0.69422093}});
        }
        LinearAlgebra::Matrix predict(LinearAlgebra::Matrix x) const override{
            return x.dot(W);
        }
        float loss(LinearAlgebra::Matrix x, LinearAlgebra::Matrix t) const override{
            LinearAlgebra::Matrix z = this->predict(x);
            LinearAlgebra::Matrix y = Functions::Activation::softmax(z);
            float loss = Functions::Loss::cross_entropy_loss(y, t);
            return loss;
        }
};

int main(void){
    SimpleNet net;
    net.W.show();
    LinearAlgebra::Vector x({0.6, 0.9});
    LinearAlgebra::Matrix p = net.predict(x.vec_to_matrix(0));
    p.show();
    std::cout << p.matrix_to_vec().max()[1] << "\n";
    LinearAlgebra::Vector t = LinearAlgebra::zeros(3);
    t.array[(int)p.matrix_to_vec().max()[1]] = 1;
    t.show();
    float loss = net.loss(x.vec_to_matrix(0), t.vec_to_matrix(0));
    std::cout << "loss = " << loss << "\n";
}

