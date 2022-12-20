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

    plane.get_normal();

    std::cout << plane.get_d() << std::endl;
    
    
    
}
