#include <vector>
#include "lib/geom.hpp"

using T = double;

int main(){
    int n = 2;
    
    geom::triangle<T> tr({3, 4, 0}, {-4, 0, 0}, {2, -3, 0});

    geom::triangle<T> tr2({-1, 0, 0}, {1, 0, 0}, {0, 1, 0});

    std::cout << tr.is_intersect_triangles(tr2) << std::endl;

}
