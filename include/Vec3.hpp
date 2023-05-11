#pragma once

#include <cmath>
#include <random>

// Returns a random real in [0,1).
double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// Returns a random real in [min,max).
double random_double(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}


// Define a 3D vector class
class Vec3 {
public:
    double x, y, z;

    Vec3() {}
    Vec3(double x, double y, double z);

    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator/(double s) const;
    double dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;
    inline double length() const;
    double lengthSquared() const;
    Vec3 normalize() const;
    //note: type qualifiers aren't allowed on static functions since they don't access the this pointer of a class
    //i.e. static functions cannot have a const or volatile type qualifier
    static Vec3 random();
    static Vec3 random(double min, double max);

};

//should be in a namespace
Vec3 operator*(double s, const Vec3& other);
Vec3 operator*(const Vec3& other, double s);
Vec3 randomInUnitSphere();


