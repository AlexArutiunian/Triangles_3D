cmake_minimum_required(VERSION 3.0)

add_executable(algo_test unit_tests.cpp)
target_link_libraries(algo_test gtest gmock pthread)