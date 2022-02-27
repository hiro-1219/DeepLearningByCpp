#include<stdio.h>
#include<fstream>
#include<iostream>
#include<string>
#include<random>
#include<vector>
#include<map>
#include<algorithm>
#include "../../header/LinearAlgebra.hpp"
#include "../../header/DeepLearning.hpp"

namespace DeepLearning::Utils{
    LinearAlgebra::Matrix get_matrix(std::vector<LinearAlgebra::Vector> batch){
        std::vector<std::vector<float>> tmp_matrix;
        for(int i = 0; i < (int)batch.size(); i++){
            tmp_matrix.push_back(batch[i].array);
        }
        LinearAlgebra::Matrix ret_matrix(tmp_matrix);
        return ret_matrix;
    }
    Dataset<LinearAlgebra::Vector, int> MNIST_DataLoader(std::string set_kinds){
        Dataset<LinearAlgebra::Vector, int> ret_dataset;
        std::vector<LinearAlgebra::Vector> ret_images;
        std::vector<int> ret_labels;
        std::vector<float> tmp_vec;
        char offset_images[16], offset_labels[8], value; 
        if(set_kinds == "test"){
            std::ifstream test_images("/home/hiroki/Project/DeepLearningByC++/data/t10k-images-idx3-ubyte", std::ios::in | std::ios::binary);
            if(!test_images) std::cout << "Error occured in test_images open" << "\n";
            std::ifstream test_labels("/home/hiroki/Project/DeepLearningByC++/data/t10k-labels-idx1-ubyte", std::ios::in | std::ios::binary);
            if(!test_labels) std::cout << "Error occured in test_labels open" << "\n";
            test_images.read(offset_images, sizeof(offset_images));
            test_labels.read(offset_labels, sizeof(offset_labels));
            for(int i = 0; i < 10000; i++){
                tmp_vec.clear();
                for(int j = 0; j < 28 * 28; j++){
                    test_images.read((char*)&value, sizeof(unsigned char));
                    tmp_vec.push_back((float)value);
                }
                ret_dataset.subject.push_back(LinearAlgebra::array(tmp_vec));
                test_labels.read((char *)&value, sizeof(unsigned char));
                ret_dataset.label.push_back(value);
            }
        }
        else if(set_kinds == "train"){
            std::ifstream train_images("/home/hiroki/Project/DeepLearningByC++/data/train-images-idx3-ubyte", std::ios::in | std::ios::binary);
            if(!train_images) std::cout << "Error occured in train_images open" << "\n";
            std::ifstream train_labels("/home/hiroki/Project/DeepLearningByC++/data/train-labels-idx1-ubyte", std::ios::in | std::ios::binary);
            if(!train_labels) std::cout << "Error occured in train_labels open" << "\n";
            train_images.read(offset_images, sizeof(offset_images));
            train_labels.read(offset_labels, sizeof(offset_labels));
            for(int i = 0; i < 60000; i++){
                tmp_vec.clear();
                for(int j = 0; j < 28 * 28; j++){
                    train_images.read((char*)&value, sizeof(unsigned char));
                    tmp_vec.push_back((float)value);
                }
                ret_dataset.subject.push_back(LinearAlgebra::array(tmp_vec));
                train_labels.read((char *)&value, sizeof(unsigned char));
                ret_dataset.label.push_back(value);
            }
        }
        return ret_dataset;
    }
}