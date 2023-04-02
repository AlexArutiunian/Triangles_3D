#include "lib/intersection.hpp"
#include "lib/geom.hpp"

using T = double;

int main(){
    geom::triangle<T> tr1({3, 0, 0}, {0, 3, 0}, {0, 0, 3});
    geom::triangle<T> tr2({3, 0, 0}, {0, 3, 0}, {0, 0, 1});

    std::cout << tr1;
}
