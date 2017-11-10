cmake_minimum_required(VERSION 3.7)
project(graph)
set(CMAKE_CXX_STANDARD 14)


# Options

option(GRAPH_BUILD_TESTS "Enable/Disable unit tests for the graph library." on)


# Add graph library

add_library(graph INTERFACE)
target_include_directories(graph INTERFACE
        include/)


# Unit tests

if (GRAPH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
