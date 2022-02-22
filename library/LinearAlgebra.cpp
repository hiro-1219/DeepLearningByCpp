#include<iostream>
#include<vector>
#include "LinearAlgebra.hpp"

LinearAlgebra::Vector::Vector(){
    this->array.resize(0);
}

LinearAlgebra::Vector::Vector(std::vector<float> a){
    this->array = a;
    check_size();
}

LinearAlgebra::Vector LinearAlgebra::Vector::operator + (LinearAlgebra::Vector v){
    LinearAlgebra::Vector c;
    for(int i = 0; i < v.size; i++){
        c.array.push_back(this->array[i] + v.array[i]);
    }
    c.check_size();
    return c;
}

LinearAlgebra::Vector LinearAlgebra::Vector::operator - (LinearAlgebra::Vector v){
    LinearAlgebra::Vector c;
    for(int i = 0; i < v.size; i++){
        c.array.push_back(this->array[i] - v.array[i]);
    }
    c.check_size();
    return c;
}

LinearAlgebra::Vector LinearAlgebra::Vector::operator * (LinearAlgebra::Vector v){
    LinearAlgebra::Vector c;
    for(int i = 0; i < v.size; i++){
        c.array.push_back(this->array[i] * v.array[i]);
    }
    c.check_size();
    return c;
}

LinearAlgebra::Vector LinearAlgebra::Vector::operator / (LinearAlgebra::Vector v){
    LinearAlgebra::Vector c;
    for(int i = 0; i < v.size; i++){
        c.array.push_back(this->array[i] / v.array[i]);
    }
    c.check_size();
    return c;
}

float LinearAlgebra::Vector::dot(LinearAlgebra::Vector v){
    float dot = 0;
    for(int i = 0; i < v.size; i++){
        //std::cout << dot << "\n";
        dot += this->array[i] * v.array[i];
    }
    return dot;
}


void LinearAlgebra::Vector::check_size(){
    this->size = this->array.size();
}

void LinearAlgebra::Vector::show(){
    std::cout << "Vector{" << this->size << "}" << "\n" << "[ ";
    for(int i = 0; i < this->size; i++){
        std::cout << this->array[i] << " ";
    }
    std::cout << "]" << "\n";
}