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
        grads["W1"].show();
        grads["B1"] = Differential::numerical_gradient(loss_W, &params["B1"]);
        grads["W2"] = Differential::numerical_gradient(loss_W, &params["W2"]);
        grads["B2"] = Differential::numerical_gradient(loss_W, &params["B2"]);
        return grads;
    }
};

void show_mnist_dataset(Utils::Dataset<LinearAlgebra::Vector, LinearAlgebra::Vector> dataset, int n){
    int cnt = 0;
    dataset.label[n].show();
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            printf("%04d ", (int)dataset.subject[n].array[cnt]);
            cnt++;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
int main(void){
    Utils::Dataset<LinearAlgebra::Vector, int> tmp_train_dataset = Utils::MNIST_DataLoader("train");
    Utils::Dataset<LinearAlgebra::Vector, int> tmp_test_dataset = Utils::MNIST_DataLoader("test");

    Utils::Dataset<LinearAlgebra::Vector, LinearAlgebra::Vector> train_dataset = Utils::onehot_encoder(tmp_train_dataset);
    Utils::Dataset<LinearAlgebra::Vector, LinearAlgebra::Vector> test_dataset = Utils::onehot_encoder(tmp_test_dataset);

    std::vector<float> train_loss;

    int iters_num = 50;
    int train_size = train_dataset.subject.size();
    int batch_size = 100;
    float learning_rate = 0.01;

    Utils::Batch<LinearAlgebra::Vector, LinearAlgebra::Vector> batch_train(train_dataset, batch_size);

    show_mnist_dataset(batch_train.dataset, 10);
    TwoLayerNet network(784, 50, 10);

    std::random_device rnd;
    std::mt19937 mt(rnd());

    std::uniform_int_distribution<> batch_random(0, (int)(train_size / batch_size));
    
    for(int i = 0; i < iters_num; i++){
        int batch_n = batch_random(mt);
        LinearAlgebra::Matrix n_label = Utils::get_matrix(batch_train.at_label(batch_n));
        LinearAlgebra::Matrix n_subject = Utils::get_matrix(batch_train.at_subject(batch_n));
        
        std::map<std::string, LinearAlgebra::Matrix> grad = network.numerical_gradient(n_subject, n_label);
        
        for(auto key : {"W1", "B1", "W2", "B2"}){
            network.params[key] = network.params[key] - learning_rate * grad[key];
        }

        float loss = network.loss(n_subject, n_label);
        train_loss.push_back(loss);
        std::cout << "[" << i << "]" << loss << "\n";
    }

    Plot::PlotGraph plot("gnuplot -persist");
    plot.plot_start();
    plot.plot(LinearAlgebra::arange(0, 50, 1), LinearAlgebra::array(train_loss), {0, 50}, {0, 10}, {"iteration", "loss"}, "red", true);
    plot.plot_end();

    return 0;
}

