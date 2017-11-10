cmake_minimum_required(VERSION 3.7)
project(test_graph)
set(CMAKE_CXX_STANDARD 14)


add_subdirectory(googletest)

add_executable(graph_unit_tests
        test_Graph.cpp
        test_PartiteGraph.cpp)
target_include_directories(graph_unit_tests PRIVATE
        ${gtest_SOURCE_DIR}/include)
target_link_libraries(graph_unit_tests
        gtest_main
        graph)
add_test(graph_unit_tests graph_unit_tests)
