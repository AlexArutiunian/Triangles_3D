#pragma once

#include <vector>
#include <cmath>
#include "geom.hpp"
#include "vector_3D.hpp"

namespace geom{
template <typename T> class segment{
private:
    vector<T> point1;
    vector<T> point2;
public:
    segment(const vector<T>& p1, const vector<T>& p2):
    point1(p1), point2(p2){
        
    }

    const vector<T>& get_point1() const{
        return point1;
    }
    vector<T>& get_point1(){
        return point1;
    }

    const vector<T>& get_point2() const{
        return point2;
    }
    vector<T>& get_point2(){
        return point2;
    }


    segment(const T* p1, const T* p2){
       
        point1.x = p1[0];
        point1.y = p1[1];
        point1.z = p1[2];

        point2.x = p2[0];
        point2.y = p2[1];
        point2.z = p2[2];

    }

    segment<T>& operator=(const segment<T>& rhs){
        point1 = rhs.point1;
        point2 = rhs.point2;
        return *this;
    }

    segment<T>& operator=(const vector<T>* points){
        point1 = points[0];
        point2 = points[1];
        return *this;
    }

    friend std::ostream& operator << (std::ostream& os, segment<T> const &A){
        os << "{" <<A.point1 << " , " << A.point2 << "}" << std::endl;
        return os;
    }

    friend std::istream& operator >> (std::istream& is, segment<T> &A){
        is >> A.point1 >> A.point2;
        return is;
    }

    ~segment(){}
};

}