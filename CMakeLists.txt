cmake_minimum_required(VERSION 3.7)
project(graph)

set(CMAKE_CXX_STANDARD 14)


option(GRAPH__DISABLE_TESTS "Disable unit tests for graph library" off)

if (!GRAPH__DISABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
