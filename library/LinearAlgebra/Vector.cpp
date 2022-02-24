#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include "../../header/LinearAlgebra.hpp"

namespace LinearAlgebra{
    // Vector
    Vector::Vector(){
        this->array.resize(0);
    }
    Vector::Vector(int n, int range0, int range1){
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_real_distribution<> rand_seed(range0, range1);
        for(int i = 0; i < n; i++){
            this->array.push_back(rand_seed(mt));
        }
        check_size();
    }

    Vector::Vector(std::vector<float> a){
        this->array = a;
        check_size();
    }

    Vector Vector::operator + (Vector v){
        Vector c;
        for(int i = 0; i < v.size; i++){
            c.array.push_back(this->array[i] + v.array[i]);
        }
        c.check_size();
        return c;
    }

    Vector Vector::operator - (Vector v){
        Vector c;
        for(int i = 0; i < v.size; i++){
            c.array.push_back(this->array[i] - v.array[i]);
        }
        c.check_size();
        return c;
    }

    Vector Vector::operator * (Vector v){
        Vector c;
        for(int i = 0; i < v.size; i++){
            c.array.push_back(this->array[i] * v.array[i]);
        }
        c.check_size();
        return c;
    }

    Vector Vector::operator * (float k){
        Vector c;
        for(int i = 0; i < this->size; i++){
            c.array.push_back(this->array[i] * k);
        }
        c.check_size();
        return c;
    }

    Vector operator * (float k, Vector v){
        Vector c;
        for(int i = 0; i < v.size; i++){
            c.array.push_back(k * v.array[i]);
        }
        c.check_size();
        return c;
    }

    Vector Vector::operator / (Vector v){
        Vector c;
        for(int i = 0; i < v.size; i++){
            c.array.push_back(this->array[i] / v.array[i]);
        }
        c.check_size();
        return c;
    }

    Vector Vector::operator / (float k){
        Vector c;
        for(int i = 0; i < this->size; i++){
            c.array.push_back(this->array[i] / k);
        }
        c.check_size();
        return c;
    }

    Vector operator / (float k, Vector v){
        Vector c;
        for(int i = 0; i < v.size; i++){
            c.array.push_back(k / v.array[i]);
        }
        c.check_size();
        return c;
    }

    float Vector::dot(Vector v){
        float dot = 0;
        for(int i = 0; i < v.size; i++){
            dot += this->array[i] * v.array[i];
        }
        return dot;
    }

    float Vector::sum(){
        float ret = 0;
        for(int i = 0; i < this->size; i++){
            ret += this->array[i];
        }
        return ret;
    }

    std::vector<float> Vector::min(){
        std::vector<float> ret_vec = this->array;
        Vector index = arange(0, this->size, 1);
        std::vector<float> ret_vec_index = index.array;
        std::sort(ret_vec_index.begin(), ret_vec_index.end(), [&ret_vec](int i1, int i2){
            return ret_vec[i1] < ret_vec[i2];
        });
        return {ret_vec[ret_vec_index[0]], ret_vec_index[0]};
    }

    std::vector<float> Vector::max(){
        std::vector<float> ret_vec = this->array;
        Vector index = arange(0, this->size, 1);
        std::vector<float> ret_vec_index = index.array;
        std::sort(ret_vec_index.begin(), ret_vec_index.end(), [&ret_vec](int i1, int i2){
            return ret_vec[i1] > ret_vec[i2];
        });
        return {ret_vec[ret_vec_index[0]], ret_vec_index[0]};
    }

    Matrix Vector::vec_to_matrix(int axis){
        std::vector<std::vector<float>> tmp_m;
        if(axis == 0){ // 列ベクトル
            tmp_m.push_back(this->array);
        }else if(axis == 1){ // 行ベクトル
            for(int i = 0; i < this->size; i++){
                std::vector<float> tmp_vec;
                tmp_vec.push_back(this->array[i]);
                tmp_m.push_back(tmp_vec);
            }
        }
        Matrix ret_m(tmp_m);
        return ret_m;
    }

    void Vector::check_size(){
        this->size = this->array.size();
    }

    void Vector::show(){
        std::cout << "Vector{" << this->size << "}" << "\n" << "[ ";
        for(int i = 0; i < this->size; i++){
            std::cout << this->array[i] << " ";
        }
        std::cout << "]" << "\n";
    }
}