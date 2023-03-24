#include <iostream>
#include "lib/matrix.hpp"
#include "lib/geom.hpp"

using T = double;

int main(){
    int n = 4;
 

    std::vector<T> p1 = {2, 0, 0};
    std::vector<T> p2 = {-1, 0, 0};
    std::vector<T> p3 = {0, 0, 1};
    
     
    geom::vector<T> v(1.0, 2.0, 1.0);

    geom::vector<T> v2 = v;

    std::cout << v * v2 << std::endl;

    v.vect_mult(v2);

    std::cout << v * v2 << std::endl;

    geom::line_segment<T> segment({2, 2, 0}, {0, 0, 0});

    geom::line_segment<T> segment2({3, 1, 0}, {3, 6, 0});

    std::cout << segment.is_intersect_segment(segment2);



}
