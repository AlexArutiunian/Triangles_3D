#include <gtest/gtest.h>
#include "../../lib/intersection.hpp"
#include <fstream>

using T = double; 

TEST(TestConstructors, segment) {
    geom::line_segment<T> segment({1, 1, 0}, {0, 0, 0});
}

int main(int argc, char **argv){

    // in this unit test it excepts that 3 test will be failed
    // if it's so - tests ok 
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}