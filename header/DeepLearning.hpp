#ifndef DEEPLEARNING_HPP
#define DEEPLEARNING_HPP
#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include "LinearAlgebra.hpp"
#include "Plot.hpp"

namespace DeepLearning{
    class BaseNetwork{
        public: 
        BaseNetwork(){}
        virtual LinearAlgebra::Matrix predict(LinearAlgebra::Matrix x) const = 0;
        virtual float loss(LinearAlgebra::Matrix x, LinearAlgebra::Matrix y) const = 0;
    };
}

namespace DeepLearning::Functions::Activation{
    LinearAlgebra::Vector sigmoid(LinearAlgebra::Vector x);       
    LinearAlgebra::Matrix sigmoid(LinearAlgebra::Matrix x);       // sigmoid
    LinearAlgebra::Vector identity_function(LinearAlgebra::Vector x);
    LinearAlgebra::Matrix identity_function(LinearAlgebra::Matrix x);
    LinearAlgebra::Vector softmax(LinearAlgebra::Vector x);
    LinearAlgebra::Matrix softmax(LinearAlgebra::Matrix x);

    LinearAlgebra::Vector step_function(LinearAlgebra::Vector x); // step
    LinearAlgebra::Vector ReLU(LinearAlgebra::Vector x);
}

namespace DeepLearning::Functions::Loss{
    float sum_squared_loss(LinearAlgebra::Vector y, LinearAlgebra::Vector t);
    float cross_entropy_loss(LinearAlgebra::Vector y, LinearAlgebra::Vector t);
    float cross_entropy_loss(std::vector<LinearAlgebra::Vector> y, std::vector<LinearAlgebra::Vector> t);
    float cross_entropy_loss(LinearAlgebra::Matrix y, LinearAlgebra::Matrix t);
}

namespace DeepLearning::Differential{
    template<class Fn> float numerical_differential(Fn function, float x){
        float h = 1e-4;
        return (function(x + h) - function(x - h)) / (2 * h);
    }
    template<class Fn> LinearAlgebra::Vector numerical_gradient(Fn function, LinearAlgebra::Vector x){
        float h = 1e-4;
        LinearAlgebra::Vector grad(x.size, 0, 1);
        LinearAlgebra::Vector tmp_x = x;
        for(int i = 0; i < x.size; i++){
            float tmp_x_val = tmp_x.array[i];
            tmp_x.array[i] = tmp_x_val + h;
            float fxh1 = function(tmp_x);
            tmp_x.array[i] = tmp_x_val - h;
            float fxh2 = function(tmp_x);
            grad.array[i] = (fxh1 - fxh2) / (2 * h);
            tmp_x = x;
        }
        return grad;
    }
    template<class Fn> LinearAlgebra::Matrix numerical_gradient(Fn function, LinearAlgebra::Matrix x){
        float h = 1e-4;
        LinearAlgebra::Matrix grad(x.size, 0, 1);
        LinearAlgebra::Matrix tmp_x = x;
        for(int i = 0; i < x.size[0]; i++){
            for(int j = 0; j < x.size[1]; j++){
                float tmp_x_val = tmp_x.array[i][j];
                tmp_x.array[i][j] = tmp_x_val + h;
                float fxh1 = function(tmp_x);
                tmp_x.array[i][j] = tmp_x_val - h;
                float fxh2 = function(tmp_x);
                grad.array[i][j] = (fxh1 - fxh2) / (2 * h);
                tmp_x = x;
            }
        }
        return grad;
    }
}

namespace DeepLearning::Utils{
    template <class T, class L> class Batch{
        public:
            std::vector<T> subject;
            std::vector<L> label;
            int batch_size;
            int batch_vec_size;
            Batch(std::vector<T> subject, std::vector<L> label, int batch_size){
                this->batch_size = batch_size;
                LinearAlgebra::Vector index_vec = LinearAlgebra::arange(0, subject.size(), 1);
                std::vector<float> index = index_vec.array;
                std::mt19937 mt;
                std::shuffle(index.begin(), index.end(), mt);
                for(int i = 0; i < (int)subject.size(); i++){
                    this->subject.push_back(subject[(int)index[i]]);
                    this->label.push_back(label[(int)index[i]]);
                }
                check_batch_vec_size();
            }
            std::vector<T> at_subject(int n){
                std::vector<T> ret_vec;
                int in_batch_size;
                if(this->batch_vec_size < (n + 1) * this->batch_size) in_batch_size = this->batch_vec_size - n * this->batch_size;
                else in_batch_size = this->batch_size;
                for(int i = n * this->batch_size; i < n * this->batch_size + in_batch_size; i++){
                    ret_vec.push_back(this->subject[i]);
                }
                return ret_vec;
            }
            std::vector<L> at_label(int n){
                std::vector<L> ret_vec;
                int in_batch_size;
                if(this->batch_vec_size < (n + 1) * this->batch_size) in_batch_size = this->batch_vec_size - n * this->batch_size;
                else in_batch_size = this->batch_size;
                for(int i = n * this->batch_size; i < n * this->batch_size + in_batch_size; i++){
                    ret_vec.push_back(this->label[i]);
                }
                return ret_vec;
            }
        private:
            void check_batch_vec_size(){
                batch_vec_size = this->subject.size();
            }
    };
    LinearAlgebra::Matrix get_matrix(std::vector<LinearAlgebra::Vector> batch);
}

namespace DeepLearning::Optimizer{
    template<class Fn> LinearAlgebra::Vector gradient_descent(Fn function, LinearAlgebra::Vector init_x, float lr = 0.01, float step_num = 100, std::vector<bool> plot_graph = {false, false}){
        LinearAlgebra::Vector x = init_x;
        std::vector<LinearAlgebra::Vector> x_vec;
        std::vector<float> z_vec;
        x_vec.push_back(x);
        z_vec.push_back(function(x));
        for(int i = 0; i < step_num; i++){
            LinearAlgebra::Vector grad = DeepLearning::Differential::numerical_gradient(function, x);
            x = x - lr * grad;
            x_vec.push_back(x);
            z_vec.push_back(function(x));
        }
        LinearAlgebra::Vector z(z_vec);
        LinearAlgebra::Matrix x_matrix = Utils::get_matrix(x_vec);
        LinearAlgebra::Vector x0 = x_matrix.get_vector(1, 0);
        LinearAlgebra::Vector x1 = x_matrix.get_vector(1, 1);
        if(plot_graph[0] == true){
            Plot::PlotGraph plot("gnuplot -persist");
            plot.plot_start();
            plot.plot_3d(function, {-3.5, 3.5}, {-4.5, 4.5}, {0, 18}, {"x0", "x1", "f(x)"}, plot_graph[1], true, "blue");
            plot.plot_3d(x0, x1, z, {-3.5, 3.5}, {-4.5, 4.5}, {0, 18}, {"x0", "x1", "f(x)"});
            plot.plot_end();
        }
        return x;
    }
}
#endif