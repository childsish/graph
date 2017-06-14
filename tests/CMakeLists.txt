cmake_minimum_required(VERSION 3.7)
project(test_graph)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)


add_executable(test_units
        test_Graph.cpp
        test_PartiteGraph.cpp)
target_include_directories(
        test_units PRIVATE
        ${gtest_SOURCE_DIR}/include
        ../include
)
target_link_libraries(test_units gtest_main)
add_test(test_units test_units)
