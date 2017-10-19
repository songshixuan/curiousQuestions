cmake_minimum_required (VERSION 3.2)
set(BOOSTLIBDIR "/usr/local/lib/")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_BUILD_TYPE Debug)                                                                                                                                                                  
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
include_directories ("/usr/lib/x86_64-linux-gnu/")
file(GLOB my_SRC              
    "*.h"                     
    "*.cpp"                   
)                             
project (joinAny)          

add_executable(joinAny ${my_SRC})
TARGET_LINK_LIBRARIES(joinAny pthread)
