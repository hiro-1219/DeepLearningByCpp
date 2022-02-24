#include<vector>
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