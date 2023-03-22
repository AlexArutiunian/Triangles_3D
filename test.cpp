#include <iostream>
#include "lib/matrix.hpp"
#include "lib/geom.hpp"

int main(){
    int n = 4;

    matrix::math_matrix<int> m(n);

    std::cout << m << std::endl;

    m(3, 3) = 7;

    std::cout << m << std::endl;



}
