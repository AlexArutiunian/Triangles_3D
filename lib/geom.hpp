#pragma once

#include <vector>
#include <cmath>


namespace geom{

template <typename T> class vector{
private:
    T x;
    T y;
    T z;
   
public:
    vector(const T& x, const T& y, const T& z): x(x), y(y), z(z){}
    
    vector<T>& operator=(const vector<T>& rhs){
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    } 

    T get_x(){
        return x;
    }
    T get_y(){
        return y;
    }
    T get_z(){
        return z;
    }
    
    vector<T>& operator-=(const vector<T>& rhs){
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;

        return *this;
    }
     
    vector<T>& operator=(T* array){
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;

    }

    T operator*(const vector<T>& rhs){
        
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }  

    vector<T>& vect_mult(const vector<T>& rhs){
        
        T temp_x = y * rhs.z - z * rhs.y;
        T temp_y = -x * rhs.z + z * rhs.x;
        T temp_z = x * rhs.y - y * rhs.x;

        x = temp_x;
        y = temp_y;
        z = temp_z;

        return *this;
   
    }
    
    ~vector(){}
};

template <typename T>
vector<T> operator-(const vector<T>& vect1, const vector<T>& vect2){
    vector<T> temp = vect1;
    temp -= vect2;
    return temp;
}


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

    vector<T> normal(){
        vector<T> normal = (vert2-vert1).vect_mult(vert3 - vert1);//N = (V2-V1) x (V3-V1)
        return normal;
    }
    
    ~triangle(){}
};

     
} // namespace end
