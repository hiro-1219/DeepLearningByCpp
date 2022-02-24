#include<iostream>
#include<vector>
#include<random>
#include "../../header/LinearAlgebra.hpp"

namespace LinearAlgebra{
    // Matrix
    Matrix::Matrix(){
        this->array.resize(0);
    }

    Matrix::Matrix(std::vector<int> n, int range0, int range1){
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_real_distribution<> rand_seed(range0, range1);
        std::vector<float> tmp_vec;
        for(int i = 0; i < n[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < n[1]; j++){
                tmp_vec.push_back(rand_seed(mt));
            }
            this->array.push_back(tmp_vec);
        }
        check_size();
    }

    Matrix::Matrix(std::vector<std::vector<float>> a){
        this->array = a;
        check_size();
    }

    Matrix Matrix::operator + (Matrix m){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < m.size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < m.size[1]; j++){
                tmp_vec.push_back(this->array[i][j] + m.array[i][j]);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix Matrix::operator - (Matrix m){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < m.size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < m.size[1]; j++){
                tmp_vec.push_back(this->array[i][j] - m.array[i][j]);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix Matrix::operator * (Matrix m){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < m.size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < m.size[1]; j++){
                tmp_vec.push_back(this->array[i][j] * m.array[i][j]);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix Matrix::operator / (Matrix m){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < m.size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < m.size[1]; j++){
                tmp_vec.push_back(this->array[i][j] / m.array[i][j]);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix Matrix::operator * (float k){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < this->size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < this->size[1]; j++){
                tmp_vec.push_back(this->array[i][j] * k);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix operator * (float k, Matrix m){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < m.size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < m.size[1]; j++){
                tmp_vec.push_back(k * m.array[i][j]);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix Matrix::operator / (float k){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < this->size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < this->size[1]; j++){
                tmp_vec.push_back(this->array[i][j] / k);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix operator / (float k, Matrix m){
        Matrix c;
        std::vector<float> tmp_vec;
        for(int i = 0; i < m.size[0]; i++){
            tmp_vec.clear();
            for(int j = 0; j < m.size[1]; j++){
                tmp_vec.push_back(k / m.array[i][j]);
            }
            c.array.push_back(tmp_vec);
        }
        c.check_size();
        return c;
    }

    Matrix Matrix::dot(Matrix m){
        Matrix c({this->size[0], m.size[1]}, 0, 1);
        std::vector<Vector> tmp_vec(2);
        for(int i = 0; i < this->size[0]; i++){
            for(int j = 0; j < m.size[1]; j++){
                tmp_vec[0] = this->get_vector(0, i);
                tmp_vec[1] = m.get_vector(1, j);
                c.array[i][j] = tmp_vec[0].dot(tmp_vec[1]);
            }
        }
        c.check_size();
        return c;
    }

    Vector Matrix::matrix_to_vec(){
        Vector ret_vec;
        if(this->size[0] == 1) ret_vec = get_vector(0, 0);
        else if(this->size[1] == 1) ret_vec = get_vector(1, 0);
        return ret_vec;
    }

    void Matrix::show(){
        std::cout << "Matrix{" << this->size[0] << " * " << this->size[1] << "}\n" << "["; 
        for(int i = 0; i < this->size[0]; i++){
            if(i == 0) std::cout << "[ ";
            else std::cout << " [ ";
            for(int j = 0; j < this->size[1]; j++){
                std::cout << this->array[i][j] << " ";
            }
            if(i == this->size[0] - 1) std::cout << "]";
            else std::cout << "]\n";
        }
        std::cout << "]\n";
    }

    void Matrix::check_size(){
        this->size.push_back(this->array.size());
        this->size.push_back(this->array[0].size());
    }

    Vector Matrix::get_vector(int axis, int n){
        std::vector<float> vec;
        if(axis == 0){ //列方向
            for(int i = 0; i < this->size[1]; i++){
                vec.push_back(this->array[n][i]);
            }
        }else if(axis == 1){ //行方向
            for(int i = 0; i < this->size[0]; i++){
                vec.push_back(this->array[i][n]);
            }
        }
        Vector ret_vec(vec);
        return ret_vec;
    }
}