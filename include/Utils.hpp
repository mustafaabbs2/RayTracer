#pragma once

#include <random>

// Returns a random real in [0,1).

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}


// Utility function to clamp a value between a minimum and maximum
double clamp(double value, double min, double max) {
    return std::fmax(min, std::fmin(value, max));
}

// Utility function to compute the dot product of two vectors
double dot(const Vec3& v, const Vec3& n) {
    return  v.x * n.x + v.y * n.y + v.z * n.z;
}

// Utility function to compute the cross product of two vectors
Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}

// Utility function to compute the reflect direction of a vector given a surface normal
Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - n * 2 * dot(v, n);
}

