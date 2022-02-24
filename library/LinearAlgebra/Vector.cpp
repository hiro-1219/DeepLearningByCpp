#include<iostream>
#include<vector>
#include<random>
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

    Vector Vector::map(float (*condition)(float i)){
        std::vector<float> tmp_vec;
        for(int i = 0; i < this->size; i++){
            tmp_vec.push_back(condition(this->array[i]));
        }
        Vector ret_vec(tmp_vec);
        return ret_vec;
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