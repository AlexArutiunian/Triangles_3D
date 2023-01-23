#include <iostream>
#include <vector>
#include "lib/geom.hpp"

using T = double;

int main(){
    int n = 2;
    std::vector<std::vector<T>> set_points = 
    {{3, 5, 7}, {1, 2, 3}, {1, 0, 1},
    {4, 1, 2}, {3, 2, 1}, {0, 1, 1}};

    std::vector<T> p1 = {3, 5, 7};
    std::vector<T> p2 = {1, 2, 3};
    std::vector<T> p3 = {1, 0, 1};
    geom::plane_3D<T> plane(p1, p2, p3);

    std::vector<T> norm1 = plane.get_normal();
    geom::plane_3D<T> plane2(set_points[3], set_points[4], set_points[5]);
    std::vector<T> norm2 = plane2.get_normal();
    
    T a[3];
    for(int i = 0; i != 3; ++i){
        a[i] = norm1[i] * norm2[i];
    }
    T scalar_ = a[0] + a[1] + a[2];
    T norma1 = 0;
    T norma2 = 0;
    for(int i = 0; i != 3; ++i){
        norma1 += (norm1[i] * norm1[i]);
        norma2 += (norm2[i] * norm2[i]);
    }

    if(abs(scalar_ / sqrt(norma1 * norma2)) == 1) std::cout << "the planes do not intersect\n";
    else std::cout << "the planes intersect\n";
    
    
    
}
