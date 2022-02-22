#ifndef DeepCpp
#include<iostream>
#include<vector>
#include<math.h>

namespace DeepCpp{
    class Vector{
    public:
        std::vector<float> array;
        int size;
        Vector();
        Vector(std::vector<float> a);
        Vector operator + (Vector v);
        Vector operator - (Vector v);
        Vector operator * (Vector v);
        Vector operator / (Vector v);
        void show();
    private:
        void check_size();
    };
}

#endif