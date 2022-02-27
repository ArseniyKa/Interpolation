cmake_minimum_required(VERSION 3.14)

if(NOT DEFINED CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "clang")
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER "clang++")
endif()

project(example1)

# add_subdirectory(src)

add_executable(example1 main.cpp)
