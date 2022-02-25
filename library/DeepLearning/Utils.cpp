#include<iostream>
#include<random>
#include<vector>
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
}