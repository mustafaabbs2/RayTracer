#pragma once
#include "Vec3.hpp"

class Ray {
public:

    Ray() {}
    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}

    const Vec3& getOrigin() const {
        return origin;
    }

    const Vec3& getDirection() const {
        return direction;
    }

    Vec3 pointAt(double t) const {
        return origin + direction * t;
    }

private:
    Vec3 origin, direction;

};