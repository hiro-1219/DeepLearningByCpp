#ifndef DEEPLEARNING_HPP
#define DEEPLEARNING_HPP
#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include "LinearAlgebra.hpp"

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
}

namespace DeepLearning::Utils{
    template <class T, class L> class Batch{
        public:
        // バッチのデータ構造はどうするべきか
        // -> std::vector<T> batch;
        // FIXME : 教師データのラベル考えてなかった
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

#endif