#ifndef LINEARALGEBRA_HPP
#define LINEARALGEBRA_HPP
#include<iostream>
#include<vector>
#include<math.h>

namespace LinearAlgebra{
    class Vector;
    class Matrix;
    class Vector{
    public:
        std::vector<float> array;      // ベクトルの要素
        int size;                      // ベクトルの大きさ
        Vector();                      // サイズ0のベクトル作成
        Vector(int n, int range0, int range1);
        Vector(std::vector<float> a);  // 引数に渡された要素でベクトルを作成
        // 四則演算
        Vector operator + (Vector v);  
        Vector operator - (Vector v);
        Vector operator * (Vector v);
        Vector operator / (Vector v);
        // スカラー演算
        Vector operator + (float k);
        friend Vector operator + (float k, Vector v);
        Vector operator - (float k);
        friend Vector operator - (float k, Vector v);
        Vector operator * (float k);
        friend Vector operator * (float k, Vector v);
        Vector operator / (float k);
        friend Vector operator / (float k, Vector v);
        float dot(Vector v); // 内積
        float sum(); // 全要素の和
        std::vector<float> min(); // 最小値(値, インデックス)
        std::vector<float> max(); // 最大値(値, インデックス)
        template<class Fn> Vector map(Fn condition){ // map関数
            std::vector<float> tmp_vec;
            for(int i = 0; i < this->size; i++){
                tmp_vec.push_back(condition(this->array[i]));
            }
            Vector ret_vec(tmp_vec);
            return ret_vec;
        }
        Matrix vec_to_matrix(int axis);  // ベクトルから行列へ変換
        void show(); // ベクトルのサイズ，要素表示
    private:
        void check_size();  // ベクトルのサイズを求める
    };
    class Matrix{
    public:
        std::vector<std::vector<float>> array; // 行列の要素
        std::vector<int> size;                 // 行列の大きさ
        Matrix();
        Matrix(std::vector<int> n, int range0, int range1);
        Matrix(std::vector<std::vector<float>> a);
        // 四則演算
        Matrix operator + (Matrix m);
        Matrix operator - (Matrix m);
        Matrix operator * (Matrix m);
        Matrix operator / (Matrix m);
        // スカラー演算
        Matrix operator * (float k);
        friend Matrix operator * (float k, Matrix m);
        Matrix operator / (float k);
        friend Matrix operator / (float k, Matrix m);
        Matrix dot(Matrix m); // 行列積
        Vector matrix_to_vec(); // 行列からベクトルへ変換
        void show(); // 行列のサイズ，要素表示
    private:
        // 行列のサイズを求める
        void check_size();
        // 行列の行，列からベクトルとして取り出す．
        Vector get_vector(int axis, int n);
    };

    Vector arange(float range0, float range1, float n); // arange
    Vector array(std::vector<float> v);                 // array
    Matrix array(std::vector<std::vector<float>> m);
    Vector maximum(Vector a, Vector b);
    Vector zeros(int n);
    Vector ones(int n);
}

namespace LinearAlgebra::BasicFunctions{
    LinearAlgebra::Vector log(LinearAlgebra::Vector x);
}
#endif