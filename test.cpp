#include <iostream>
#include "lib/matrix.hpp"
#include "lib/geom.hpp"
#include "lib/intersection.hpp"

using T = double;

int main(){
    
   

    geom::triangle<T> tr1({0, 0, 3}, {0, 3, 0}, {3, 0, 0});
    geom::triangle<T> tr2({0, 0, 1}, {4, 1, 0}, {1, 4, 0});
    
    std::cout << std::boolalpha << geom::is_intersect_triangles_3D(tr1, tr2) << std::endl;


   

    

}
