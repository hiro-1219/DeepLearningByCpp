#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include "./header/LinearAlgebra.hpp"
#include "./header/DeepLearning.hpp"
#include "./header/Plot.hpp"
using namespace DeepLearning;

class TwoLayerNet : public BaseNetwork{
public:
    std::map<std::string, LinearAlgebra::Matrix> params;
    TwoLayerNet(int input_size, int hidden_size, int output_size, float weight_init_std=0.01){
        this->params["W1"] = weight_init_std * LinearAlgebra::array_randn({input_size, hidden_size});
        this->params["B1"] = LinearAlgebra::zeros(hidden_size).vec_to_matrix(0);
        this->params["W2"] = weight_init_std * LinearAlgebra::array_randn({hidden_size, output_size});
        this->params["B2"] = LinearAlgebra::zeros(output_size).vec_to_matrix(0);
    }
    LinearAlgebra::Matrix predict(LinearAlgebra::Matrix x){
        LinearAlgebra::Matrix W1, W2, B1, B2;
        W1 = this->params["W1"]; W2 = this->params["W2"];
        B1 = this->params["B1"]; B2 = this->params["B2"];
        LinearAlgebra::Matrix a1 = x.dot(W1) + B1;
        LinearAlgebra::Matrix z1 = Functions::Activation::sigmoid(a1);
        LinearAlgebra::Matrix a2 = z1.dot(W2) + B2;
        LinearAlgebra::Matrix y = Functions::Activation::softmax(a2);
        return y;
    }
    float loss(LinearAlgebra::Matrix x, LinearAlgebra::Matrix t){
        LinearAlgebra::Matrix y = this->predict(x);
        return Functions::Loss::cross_entropy_loss(y, t);
    }
    float accuracy(std::vector<LinearAlgebra::Vector> x, std::vector<LinearAlgebra::Vector> t){
        std::vector<LinearAlgebra::Vector> y;
        float accuracy_cnt = 0;
        for(int i = 0; i < (int)x.size(); i++){
            LinearAlgebra::Matrix tmp_y = this->predict(x[i].vec_to_matrix(0));
            y.push_back(tmp_y.matrix_to_vec());
            if(y[i].max()[1] == t[i].max()[1]) accuracy_cnt += 1;
        }
        return accuracy_cnt / (float)x.size();
    }
    std::map<std::string, LinearAlgebra::Matrix> numerical_gradient(LinearAlgebra::Matrix x, LinearAlgebra::Matrix t){
        auto loss_W = [&x, &t, this](LinearAlgebra::Matrix* W){return this->loss(x, t);};
        std::map<std::string, LinearAlgebra::Matrix> grads;
        grads["W1"] = Differential::numerical_gradient(loss_W, &params["W1"]);
        grads["B1"] = Differential::numerical_gradient(loss_W, &params["B1"]);
        grads["W2"] = Differential::numerical_gradient(loss_W, &params["W2"]);
        grads["B2"] = Differential::numerical_gradient(loss_W, &params["B2"]);
        return grads;
    }
};

int main(void){
    Utils::Dataset<LinearAlgebra::Vector, int> train_dataset = Utils::MNIST_DataLoader("train");
    Utils::Dataset<LinearAlgebra::Vector, int> test_dataset = Utils::MNIST_DataLoader("test"); 
    int cnt = 0;
    std::cout << train_dataset.label[0] << "\n";
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            printf("%04d ", (int)train_dataset.subject[0].array[cnt]);
            cnt++;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

