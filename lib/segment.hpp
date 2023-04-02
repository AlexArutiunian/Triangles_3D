#pragma once

#include <vector>
#include <cmath>
#include "geom.hpp"
#include "vector_3D.hpp"




// PLIZ RENAME line_segment to segment

namespace geom{
template <typename T> class line_segment{
private:
    vector<T> point1;
    vector<T> point2;
public:
    line_segment(const vector<T>& p1, const vector<T>& p2):
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


    line_segment(const T* p1, const T* p2){
       
        point1.x = p1[0];
        point1.y = p1[1];
        point1.z = p1[2];

        point2.x = p2[0];
        point2.y = p2[1];
        point2.z = p2[2];

    }

    line_segment<T>& operator=(const line_segment<T>& rhs){
        point1 = rhs.point1;
        point2 = rhs.point2;
        return *this;
    }

    line_segment<T>& operator=(const vector<T>* points){
        point1 = points[0];
        point2 = points[1];
        return *this;
    }



    // it is for plane 2D

    ~line_segment(){}
};

}