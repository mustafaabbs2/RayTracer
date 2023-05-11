#pragma once

#include "Constants.hpp"
#include "Utils.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {

public:
	Camera(const double aspect_ratio);
    Ray getRay(double x, double y);

private:
    Vec3 origin, horizontal, vertical, lower_left_corner;

};