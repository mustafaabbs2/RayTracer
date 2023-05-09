#pragma once

//Have a Sphere derived


#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hitter.hpp"


class Sphere : public Hitter {

public:
    Vec3 _sphereCenter;
    double _sphereRadius;

    Sphere() {}
    Sphere(const Vec3& center, double radius) : _sphereCenter(center), _sphereRadius(radius) {}

    virtual bool hit(const Ray& ray, const Vec3& center, double radius) const override;
};


//calculate the "t" for which A + tB hits the sphere
bool Sphere::hit(const Ray& ray, const Vec3& center, double radius) {
    Vec3 oc = ray.getOrigin() - center;
    auto a = dot(ray.getDirection(), ray.getDirection());
    auto b = 2 * dot(oc, ray.getDirection());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) { //no real solutions
        return false;
    }
    else {//one or two solutions
        return (-b - std::sqrt(discriminant)) / (2 * a);
    }
}


