#include <iostream>
#include "lib/intersection.hpp"
#include "lib/geom.hpp"

using T = double;

int main(){
    
    geom::line_segment<T> seg1({0, 0, 0}, {1, 1, 0});
    geom::line_segment<T> seg2({3, 0, 0}, {1, 3, 0});

    seg1 = {{0, 1, 0}, {1, 0, 0}};
    seg2 = {{2, -1, 0}, {-1, 2, 0}};

    std::cout << std::boolalpha << is_intersect_segment(seg2, seg1) << std::endl;

    std::cout << std::boolalpha << is_intersect_segment(seg1, seg2) << std::endl;

}
