#include <iostream>
#include <vector>
#include <unordered_map>
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

    std::vector<unsigned int> num_int;
    std::unordered_map<unsigned int, unsigned int> num_intersect;

    for(int i = 0; i != n - 1; ++i){
        for(int j = i; j != n - 1; ++j){
            if(geom::is_intersect_triangles_3D(triangles[j], triangles[j + 1])){
                auto founder_fst = num_intersect.find(j);
                auto founder_snd = num_intersect.find(j + 1);
                if(founder_fst == num_intersect.end()){
                    num_intersect[j] = j + 1;
                }
                if(founder_snd == num_intersect.end()){
                    num_intersect[j + 1] = j + 2;
                }
            }
                
        }        
    }
    for(auto x : num_intersect)
        std::cout << x.second << ' ';
    std::cout << '\n';    
}
/*
6
1 0 0 0 1 0 0 0 1
3 0 0 0 3 0 0 0 3
0 0 0 0 0 4 0 4 0
0 0 2 4 1 0 1 4 0
0 0 10 3 7 0 7 3 0
0 -4 0 0 -6 0 2 -5 0

except: 3 4

*/