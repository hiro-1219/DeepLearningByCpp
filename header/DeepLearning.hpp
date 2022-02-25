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
}

namespace DeepLearning::Utils{
    template <class T> class Batch{
        public:
        // バッチのデータ構造はどうするべきか
        // -> std::vector<T> batch;
            std::vector<T> batch;
            int batch_size;
            int batch_vec_size;
            Batch(std::vector<T> subject, int batch_size){
                this->batch_size = batch_size;
                this->batch = subject;
                std::mt19937 mt;
                std::shuffle(this->batch.begin(), this->batch.end(), mt);
                check_batch_vec_size();
            }
            std::vector<T> at(int n){
                std::vector<T> ret_vec;
                int in_batch_size;
                if(this->batch_vec_size < (n + 1) * this->batch_size) in_batch_size = this->batch_vec_size - n * this->batch_size;
                else in_batch_size = this->batch_size;
                for(int i = n * this->batch_size; i < n * this->batch_size + in_batch_size; i++){
                    ret_vec.push_back(this->batch[i]);
                }
                return ret_vec;
            }
        private:
            void check_batch_vec_size(){
                batch_vec_size = this->batch.size();
            }
    };
    LinearAlgebra::Matrix get_matrix(std::vector<LinearAlgebra::Vector> batch);
}

#endif