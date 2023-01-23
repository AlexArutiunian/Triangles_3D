#include <iostream>
#include "lib/matrix.hpp"

int main(){
    std::initializer_list<int> lst = {3, 4, 0, 1};
    matrix::math_matrix<int> m(2, lst);
    std::cout << m;
}