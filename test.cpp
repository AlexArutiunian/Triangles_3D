#include <iostream>
#include "lib/matrix.hpp"
#include "lib/geom.hpp"
#include "lib/intersection.hpp"

using T = double;

int main(){
    
    geom::triangle<T> tr({0, 0, 0}, {1, 0, 0}, {0, 1, 0});
    geom::vector<T> point(0, 0, 1);

    geom::triangle<T> tr1({0, 0, 3}, {0, 3, 0}, {3, 0, 0});
    geom::triangle<T> tr2({0, 0, 1}, {4, 1, 0}, {1, 4, 0});
    
    std::vector<T> d(3);

    d = geom::distance(tr1, tr2);



    std::cout << std::boolalpha << geom::is_intersect_triangles_3D(tr1, tr2) << std::endl;

    tr1 = {{0, 0, 3}, {0, 3, 0}, {3, 0, 0}};
    tr2 = {{0, 0, 5}, {4, 1, 0}, {1, 4, 0}};
    std::cout << std::boolalpha << geom::is_intersect_triangles_3D(tr1, tr2) << std::endl;

    std::cout << geom::dist_between_point_and_triangle(tr, point) << std::endl;

    

}
