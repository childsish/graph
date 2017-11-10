cmake_minimum_required(VERSION 3.7)
project(test_graph)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)


# test Graph

add_executable(graph_test_graph
        test_Graph.cpp)
target_include_directories(graph_test_graph PRIVATE
        ${gtest_SOURCE_DIR}/include)
target_link_libraries(graph_test_graph
        gtest_main
        graph)
add_test(graph_test_graph graph_test_graph)


# test PartiteGraph

add_executable(graph_test_partite_graph
        test_PartiteGraph.cpp)
target_include_directories(graph_test_partite_graph PRIVATE
        ${gtest_SOURCE_DIR}/include)
target_link_libraries(graph_test_partite_graph
        gtest_main
        graph)
add_test(graph_test_partite_graph graph_test_partite_graph)
