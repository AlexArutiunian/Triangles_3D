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



    v.vect_mult(v2);


    geom::line_segment<T> segment({0, 1, 0}, {1, 3, 0});

    geom::line_segment<T> segment2({1, 0, 0}, {0, 2, 0});

    std::cout << segment.is_intersect_segment(segment2) << std::endl;


    geom::triangle<T> tr({1, 0, 0}, {-1, 0, 0}, {0, 2, 0});

    geom::triangle<T> tr2({0, 1, 0}, {2, 1, 0}, {1, 3, 0});

    std::cout << tr.is_intersect_triangles(tr2);




}
