#pragma once

#include <vector>
#include "matrix.hpp"

namespace geom{

template <typename T> class plane_3D{
private:
    T a, b, c, d;
    std::vector<T> norm;
public:
    plane_3D(T c1, T c2, T c3, T c4){
        a = c1;
        b = c2;
        c = c3;
        d = c4;
        norm = {a, b, c};
    }
    plane_3D(const std::vector<T>& p1, const std::vector<T>& p2, const std::vector<T>& p3){
        matrix::math_matrix<T> m_a(2, {p2[1] - p1[1], p2[2] - p1[2], p3[1] - p2[1], p3[2] - p2[2]});
        matrix::math_matrix<T> m_b(2, {p2[0] - p1[0], p2[2] - p1[2], p3[0] - p2[0], p3[2] - p2[2]});
        matrix::math_matrix<T> m_c(2, {p2[0] - p1[0], p2[1] - p1[1], p3[0] - p2[0], p3[1] - p2[1]});

        
        a = m_a.det();
        b = -(m_b.det());
        c = m_c.det();
        d = - p1[1] * b - p1[0] * a - p1[2] * c;   
        norm = {a, b, c};
    } 
    plane_3D(const std::vector<std::vector<T>>& points){
        
    }

    std::vector<T> get_normal(){
        std::cout << "{ ";
        for(auto i : norm) std::cout << i << " ";
        std::cout << "}\n";
        return norm;
    }
    
    T get_d(){
        return d;
    }
};  
     
} // namespace end