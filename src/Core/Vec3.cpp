
#include "Vec3.hpp"
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


    Vec3::Vec3() {}
    Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 Vec3::operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 Vec3::operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }


    Vec3 Vec3::operator/(double s) const {
        return Vec3(x / s, y / s, z / s);
    }

    double Vec3::dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }


    Vec3 Vec3::cross(const Vec3& v) const {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    inline double Vec3::length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    double Vec3::lengthSquared() const {
        return (x * x + y * y + z * z);
    }

    Vec3 Vec3::normalize() const { //use it to make a unit vector
        double len = length();
        return Vec3(x / len, y / len, z / len);
    }
    //note: type qualifiers aren't allowed on static functions since they don't access the this pointer of a class
    //i.e. static functions cannot have a const or volatile type qualifier
    Vec3 Vec3::random() {
        return Vec3(random_double(), random_double(), random_double());
    }

    Vec3 Vec3::random(double min, double max) {
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }


//define binary operators outside to allow dual sided operations
Vec3 operator*(double s, const Vec3& other) {
    return Vec3(other.x * s, other.y * s, other.z * s);
}

Vec3 operator*(const Vec3& other, double s) {
    return Vec3(other.x * s, other.y * s, other.z * s);
}

Vec3 randomInUnitSphere() {
    while (true) {
        auto p = Vec3::random(-1, 1);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}
