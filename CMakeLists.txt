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
    src/Core/Metal.cpp
    src/Core/Lambertian.cpp
    src/Core/Ray.cpp
    src/Core/Vec3.cpp
    src/Core/Sphere.cpp
    src/Core/Camera.cpp
    src/Writers/PPMWriter.cpp
    src/Utils/Utils.cpp
    src/Utils/Logger.cpp
)

# Add executable target
add_executable(RayTracer ${SOURCES})

#find_package(Boost REQUIRED)
#if(Boost_FOUND)
#    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
#else()
#    message(FATAL_ERROR "Could NOT find Boost (missing: Boost_INCLUDE_DIR)")
#endif()

set(Boost_INCLUDE_DIRS "D:\\Mustafa\\gil\\include")

include_directories(${Boost_INCLUDE_DIRS})


# Add include directories
target_include_directories(RayTracer PRIVATE 
${Boost_INCLUDE_DIRS}
include/)



