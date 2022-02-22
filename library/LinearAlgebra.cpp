#include<iostream>
#include<vector>
#include "DeepCpp.hpp"

DeepCpp::Vector::Vector(){
    this->array.resize(0);
}

DeepCpp::Vector::Vector(std::vector<float> a){
    this->array = a;
    check_size();
}

DeepCpp::Vector DeepCpp::Vector::operator + (DeepCpp::Vector v){
    DeepCpp::Vector c;
    for(int i = 0; i < v.size; i++){
        c.array.push_back(this->array[i] + v.array[i]);
    }
    c.check_size();
    return c;
}

DeepCpp::Vector DeepCpp::Vector::operator - (DeepCpp::Vector v){
    DeepCpp::Vector c;
    for(int i = 0; i < v.size; i++){
        c.array.push_back(this->array[i] - v.array[i]);
    }
    c.check_size();
    return c;
}


void DeepCpp::Vector::check_size(){
    this->size = this->array.size();
}

void DeepCpp::Vector::show(){
    std::cout << "Vector{" << this->size << "}" << "\n" << "[ ";
    for(int i = 0; i < this->size; i++){
        std::cout << this->array[i] << " ";
    }
    std::cout << "]" << "\n";
}