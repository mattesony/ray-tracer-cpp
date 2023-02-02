cmake_minimum_required(VERSION 3.16)
project(RayTracerTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

