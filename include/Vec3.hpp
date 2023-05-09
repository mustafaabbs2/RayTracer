#pragma once
#include <cmath>

// Define a 3D vector class
class Vec3 {
public:
    double x, y, z;

    Vec3() {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }


    Vec3 operator/(double s) const {
        return Vec3(x / s, y / s, z / s);
    }

    double dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }


    Vec3 cross(const Vec3& v) const {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() const { //use it to make a unit vector
        double len = length();
        return Vec3(x / len, y / len, z / len);
    }

};

//define binary operators outside to allow dual sided operations
Vec3 operator*(double s, const Vec3& other) {
    return Vec3(other.x * s, other.y * s, other.z * s);
}

Vec3 operator*(const Vec3& other, double s) {
    return Vec3(other.x * s, other.y * s, other.z * s);
}


