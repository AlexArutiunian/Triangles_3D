#include <iostream>
#include "lib/intersection.hpp"
#include "lib/segment.hpp"
#include "lib/triangle.hpp"
#include "lib/vector_3D.hpp"

using T = double;

int main(){
    
    geom::triangle<T> seg1({0, 0, -1}, {1, 1, -3}, {4, 5, -9});
    geom::triangle<T> seg2({3, 0, 1}, {1, 3, 4}, {4, 5, 6});

    std::cout << check_oktan(seg1, seg2) << std::endl;
}
