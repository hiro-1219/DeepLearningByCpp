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
}