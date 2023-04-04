#pragma once

#include <vector>
#include <cmath>
#include "geom.hpp"
#include "vector_3D.hpp"
#include "segment.hpp"



namespace geom{
template <typename T> class triangle{
private:
    vector<T> vert1;
    vector<T> vert2;
    vector<T> vert3;

public:    
    triangle(const vector<T> vert1, const vector<T> vert2, const vector<T> vert3):
    vert1(vert1), vert2(vert2), vert3(vert3){}

    triangle<T>& operator=(const triangle<T>& rhs){
        this->vert1 = rhs.vert1;
        this->vert2 = rhs.vert2;
        this->vert3 = rhs.vert3;

        return *this;
    }

    triangle<T>& operator=(const vector<T>* rhs){
        this->vert1 = rhs[0];
        this->vert2 = rhs[1];
        this->vert3 = rhs[2];

        return *this;
    }

    vector<T>& get_v1(){
        return vert1;
    }

    const vector<T>& get_v1() const{
        return vert1;
    }

    vector<T>& get_v2(){
        return vert2;
    }

    const vector<T>& get_v2() const{
        return vert2;
    }

    vector<T>& get_v3(){
        return vert3;
    }

    const vector<T>& get_v3() const{
        return vert3;
    }

    vector<T> normal() const{
        vector<T> normal = (vert2 - vert1).vect_mult(vert3 - vert1);//N = (V2-V1) x (V3-V1)
        return normal;
    }
    
    ~triangle(){}
};

} // namespace end