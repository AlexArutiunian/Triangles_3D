cmake_minimum_required(VERSION 3.0)

add_executable(unit_test unit_tests.cpp)
target_link_libraries(unit_test gtest gmock pthread)