cmake_minimum_required(VERSION 3.5)

project(RayTracer)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

# Add executable target
add_executable(RayTracer src/main.cpp)

# Add include directories
target_include_directories(RayTracer PRIVATE include/)

