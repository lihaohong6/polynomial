cmake_minimum_required(VERSION 3.8)
project(Polynomial)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp big_integer.cpp big_integer.h polynomial.cpp polynomial.h helper.cpp helper.h)
add_executable(Polynomial ${SOURCE_FILES})