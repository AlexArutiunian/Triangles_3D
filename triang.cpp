#include <iostream>
#include "lib/intersection.hpp"
#include "lib/geom.hpp"

using T = double;

int main(){
    
    geom::segment<T> seg1({0, 0, 0}, {1, 1, 0});
    geom::segment<T> seg2({3, 0, 0}, {1, 3, 0});

    std::cout << seg1 << "\n" << seg2 << std::endl;
}
