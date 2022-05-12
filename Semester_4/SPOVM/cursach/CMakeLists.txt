cmake_minimum_required(VERSION 3.17)
project(cursach)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "$ {CMAKE_CXX_FLAGS} -static-libstd—++ -static-libgcc")
add_executable(cursach main.cpp)