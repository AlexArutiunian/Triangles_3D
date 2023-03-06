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

        
        a = m_a.det_Gauss();
        b = -(m_b.det_Gauss());
        if(abs(b) == 0) b = 0;
        c = m_c.det_Gauss();
        d = - p1[1] * b - p1[0] * a - p1[2] * c;  
        if(abs(d) == 0) d = 0; 
        norm = {a, b, c};
    } 
    plane_3D(const std::vector<std::vector<T>>& points){
        
    }

    std::vector<T> get_normal(){
        
        return norm;
    }

    void print_normal(){
        std::cout << "{ ";
        for(auto i : norm) std::cout << i << " ";
        std::cout << "}\n";
    }
    
    T get_d(){
        return d;
    }

   
}; 

  

template <typename T> class line{
private:
    std::vector<T> lp1;
    std::vector<T> lp2;



public:
    line(const std::vector<T>& line_point1, const std::vector<T>& line_point2){
        lp1 = line_point1;
        lp2 = line_point2;
    }
 
    bool line_up_point(const std::vector<T>& point, plane_3D<T>& plane){
        T ax = this->lp1[0] - this->lp2[0];
        T ay = this->lp1[1] - this->lp2[1];
        T az = this->lp1[2] - this->lp2[2];

        T C = (plane.get_normal())[2];
        T B = (plane.get_normal())[1];
        T A = (plane.get_normal())[0];
        T D = plane.get_d();
       

        if(ax != 0){
            T noname_ = (ay / ax) * point[0] + lp1[1] - (ay / ax) * lp1[0];
            std::cout << "y = " << (ay / ax) << " * x + " << lp1[1] << " - " << (ay / ax) << " * " << lp1[0] << std::endl;
            return noname_ > point[1];
        }
            
        else if(ay != 0){
            T x = lp1[0];
            std::cout << "x = " << x << std::endl;
            return x > point[0];
    
        }
        

    }

};

template <typename T> struct triangle{
    bool point_is_in_triangle(std::vector<T>& p1, std::vector<T>& p2, std::vector<T>& p3, std::vector<T>& point){

        for(int i = 0; i != 2; ++i){
            p2[i] -= p1[i];
            p3[i] -= p1[i];
            point[i] -= p1[i];
        }

        T m = (point[0] * p2[1] - point[1] * p2[0]) / (p3[0] * p2[1] - p3[1] * p2[0]);

        if(m >= 0 && m <= 1){
            T l = (point[0] - m * p3[0]) / p2[0];
            if(l >= 0 && ((m + l) <= 1)) return true;
        }

        return false;
       




    }


};  
     
} // namespace end