cmake_minimum_required(VERSION 3.5)

project(RayTracer)

message("Configuring RayTracer..")

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/Core/Color.cpp
    src/Core/HitterList.cpp
    src/Core/Material.cpp
    src/Core/Ray.cpp
    src/Core/Vec3.cpp
    src/Core/Sphere.cpp
    src/Core/Camera.cpp
    src/Writers/PPMWriter.cpp
    src/Utils/Utils.cpp
)

# Add executable target
add_executable(RayTracer ${SOURCES})

# Add include directories
target_include_directories(RayTracer PRIVATE include/)

