cmake_minimum_required(VERSION 3.7)
project(graph)

set(CMAKE_CXX_STANDARD 14)

option(GRAPH_BUILD_TESTS "Disable unit tests for graph library" on)

include_directories(include)
file(COPY ${PROJECT_SOURCE_DIR}/include DESTINATION ${PROJECT_BINARY_DIR})

if (GRAPH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
