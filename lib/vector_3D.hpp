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

    vector<T>& operator-=(const vector<T>& rhs){
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;

        return *this;
    }

    vector<T>& operator=(T* array){
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;

    }

    T operator*(const vector<T>& rhs) const{
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

    friend std::ostream& operator<<(std::ostream& os, vector<T> const &A){
        os << "(" << A.x << "," << A.y << "," << A.z << ")";
        return os;
    }
    friend std::istream& operator >> (std::istream& is, vector<T>& A){
        is >> A.x >> A.y >> A.z;
        return is;
    }
    
    ~vector(){}
};

template <typename T>
vector<T> operator-(const vector<T>& vect1, const vector<T>& vect2){
    vector<T> temp = vect1;
    temp -= vect2;
    return temp;
}

template <typename T>
vector<T> operator+(const vector<T>& vect1, const vector<T>& vect2){
    vector<T> temp = vect1;
    temp += vect2;
    return temp;
}
}