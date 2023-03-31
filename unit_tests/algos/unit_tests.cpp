#include <gtest/gtest.h>
#include "../../lib/intersection.hpp"
#include <fstream>

using T = double;

TEST(Intersect2D, segments){
    geom::line_segment<T> seg1({0, 0, 0}, {1, 1, 0});
    geom::line_segment<T> seg2({3, 0, 0}, {1, 3, 0});

    EXPECT_FALSE(is_intersect_segment(seg1, seg2));

    seg1 = {{0, 0, 0}, {1, 1, 0}};
    seg2 = {{0, 1, 0}, {1, 0, 0}};

    

    EXPECT_TRUE(is_intersect_segment(seg1, seg2));
}

TEST(Intersect2D, triangles){
    geom::triangle<T> tr1({1, 0, 0}, {-1, 0, 0}, {0, 2, 0});
    geom::triangle<T> tr2({0, 0, 0}, {1, 2, 0}, {2, 0, 0});
    EXPECT_TRUE(is_intersect_triangles(tr1, tr2));

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{5, 0, 0}, {4, 2, 0}, {3, 0, 0}};
    EXPECT_FALSE(is_intersect_triangles(tr1, tr2));

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{-1, 0, 0}, {-2, 2, 0}, {-3, 0, 0}};
    EXPECT_TRUE(is_intersect_triangles(tr1, tr2));

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{2, 3, 0}, {0, 5, 0}, {1, 6, 0}};
    EXPECT_FALSE(is_intersect_triangles(tr1, tr2));

    tr1 = {{1, 0, 0}, {-1, 0, 0}, {0, 2, 0}};
    tr2 = {{0, 1, 0}, {-2, 4, 0}, {-1, 5, 0}};
    EXPECT_TRUE(is_intersect_triangles(tr1, tr2));


}

int main(int argc, char **argv){

    // in this unit test it excepts that 3 test will be failed
    // if it's so - tests ok 
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}