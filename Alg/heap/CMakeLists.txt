cmake_minimum_required(VERSION 3.8)
project(heap)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(SOURCE_FILES
        main.cpp heap.cpp heap.h)

add_executable(heap ${SOURCE_FILES})