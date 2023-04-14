cmake_minimum_required(VERSION 3.25)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET csrlib)

project(${TARGET} VERSION 1.0)
add_executable(${TARGET} main.cpp csrlib.cpp)

