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
        Vector(std::vector<float> a);  // 引数に渡された要素でベクトルを作成
        // 四則演算
        Vector operator + (Vector v);  
        Vector operator - (Vector v);
        Vector operator * (Vector v);
        Vector operator / (Vector v);
        // 行列積
        float dot(Vector v); // 内積
        // 行列のサイズ，要素表示
        void show();
    private:
        // 行列のサイズを求める
        void check_size();
    };
}

#endif