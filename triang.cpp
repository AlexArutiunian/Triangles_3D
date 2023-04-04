#include <iostream>
#include <vector>
#include "lib/intersection.hpp"
#include "lib/geom.hpp"

using T = double;

int main(){
    unsigned int n = 0;

    std::cin >> n;

    std::vector<geom::triangle<T>> triangles(n);

    for(int i = 0; i != n; ++i){
        std::cin >> triangles[i];
    }

    unsigned int count = 0;

    for(int i = 0; i != n - 1; ++i){
        for(int j = i; j != n - 1; ++j){
            if(geom::is_intersect_triangles_3D(triangles[j], triangles[j + 1]))
                count += 1;
        }        
    }

    std::cout << count << std::endl;

    
}
