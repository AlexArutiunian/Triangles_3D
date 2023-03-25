#include <iostream>
#include "lib/matrix.hpp"
#include "lib/geom.hpp"

using T = double;

int main(){
    

    geom::triangle<T> tr1({1, 0, 0}, {-1, 0, 0}, {0, 2, 0});

    geom::triangle<T> tr2({0, 0, 0}, {1, 2, 0}, {2, 0, 0});

    std::cout << std::boolalpha << tr1.is_intersect_triangles(tr2) << std::endl;

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{5, 0, 0}, {4, 2, 0}, {3, 0, 0}};

    std::cout << std::boolalpha << tr1.is_intersect_triangles(tr2) << std::endl;

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{-1, 0, 0}, {-2, 2, 0}, {-3, 0, 0}};

    std::cout << std::boolalpha << tr1.is_intersect_triangles(tr2) << std::endl;

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{2, 3, 0}, {0, 5, 0}, {1, 6, 0}};

    std::cout << std::boolalpha << tr1.is_intersect_triangles(tr2) << std::endl;

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{0, 1, 0}, {-2, 4, 0}, {-1, 5, 0}};

    std::cout << std::boolalpha << tr1.is_intersect_triangles(tr2) << std::endl;


}
