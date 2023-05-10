#pragma once

#include "Constants.hpp"
#include "Utils.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {

public:
	Camera(const double aspect_ratio) {

        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        origin=  Vec3(0, 0, 0);
        horizontal = Vec3(viewport_width, 0, 0);
        vertical = Vec3(0, viewport_height, 0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);    
    
    }

  
    Ray getRay(double x, double y) {

        return Ray(origin, lower_left_corner + x * horizontal + y * vertical - origin);

     }
private:
    Vec3 origin, horizontal, vertical, lower_left_corner;


};