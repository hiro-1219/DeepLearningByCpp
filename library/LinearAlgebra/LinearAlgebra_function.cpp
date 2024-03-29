#include<vector>
#include<random>
#include "../../header/LinearAlgebra.hpp"

namespace LinearAlgebra{
    Vector arange(float range0, float range1, float n){
        std::vector<float> tmp_vec;
        float push_value = range0;
        while(range1 > push_value){
            tmp_vec.push_back(push_value);
            push_value += n;
        }
        Vector ret_vec(tmp_vec);
        return ret_vec;
    }

    Vector array(std::vector<float> v){
        Vector ret_vec(v);
        return ret_vec;
    }

    Vector array_random(int n, int range0, int range1){
        Vector ret_vec(n, range0, range1);
        return ret_vec;
    }

    Vector array_randn(int n){
        std::vector<float> tmp_vec;
        std::random_device seed_gen;
        std::default_random_engine engine(seed_gen());
        std::normal_distribution<> dist(0.0, 1.0);
        for(int i = 0; i < n; i++){
            tmp_vec.push_back(dist(engine));
        }
        return array(tmp_vec);
    }

    Matrix array(std::vector<std::vector<float>> m){
        Matrix ret_matrix(m);
        return ret_matrix;
    }

    Matrix array_random(std::vector<int> n, int range0, int range1){
        Matrix ret_matrix(n, range0, range1);
        return ret_matrix;
    }

    Matrix array_randn(std::vector<int> n){
        std::vector<std::vector<float>> tmp_matrix;
        std::random_device seed_gen;
        std::default_random_engine engine(seed_gen());
        std::normal_distribution<> dist(0.0, 1.0);
        std::vector<float> tmp_vec;
        for(int i = 0; i < n[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < n[1]; j++){
                tmp_vec.push_back(dist(engine));
            }
            tmp_matrix.push_back(tmp_vec);
        }
        return array(tmp_matrix);
    }

    Vector maximum(Vector a, Vector b){
        std::vector<float> tmp_vec;
        for(int i = 0; i < a.size; i++){
            if(a.array[i] > b.array[i]) tmp_vec.push_back(a.array[i]);
            else if(a.array[i] <= b.array[i]) tmp_vec.push_back(b.array[i]);
        }
        Vector ret_vec(tmp_vec);
        return ret_vec;
    }

    Vector zeros(int n){
        std::vector<float> tmp_vec(n, 0);
        Vector ret_vec(tmp_vec);
        return ret_vec;
    }

    Vector ones(int n){
        std::vector<float> tmp_vec(n, 1);
        Vector ret_vec(tmp_vec);
        return ret_vec;
    }
}