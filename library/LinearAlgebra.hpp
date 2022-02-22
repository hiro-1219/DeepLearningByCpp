#ifndef LinearAlgebra
#include<iostream>
#include<vector>
#include<math.h>

namespace LinearAlgebra{
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
        // ベクトル積
        float dot(Vector v); // 内積
        // ベクトルのサイズ，要素表示
        void show();
    private:
        // ベクトルのサイズを求める
        void check_size();
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
        // 行列積
        Matrix dot(Matrix m);
        // 行列のサイズ，要素表示
        void show();
    private:
        // 行列のサイズを求める
        void check_size();
        // 行列の行，列からベクトルとして取り出す．
        Vector get_vector(int axis, int n);
    };
}

#endif