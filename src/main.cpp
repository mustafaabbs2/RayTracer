#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"

#include "Sphere.hpp"

#define RAYTRACER 1


//Utility function to return the ray color
Color rayColor(const Ray& ray) {

    /* Define the scene objects here */

    //Sphere
    {
        Vec3 sphereCenter(0, 0, -1);
        auto sphereRadius = 0.5;
        Color sphereColor(1, 0, 0);
        Sphere sphere(sphereCenter, sphereRadius, sphereColor);
        auto t = intersectSphere(ray, sphere._sphereCenter, sphere._sphereRadius);

        if (t > 0)
        {
            //return sphere._sphereColor; /this is a solution without shading..
            auto pt = ray.pointAt(t); //point coordinates at t (intersection)
            auto normal = (pt - sphere._sphereCenter).normalize();
            return 0.5 * Color(normal.x + 1, normal.y + 1, normal.z + 1);
        }

    }

    //Background
    {
        auto unitDirection = ray.getDirection().normalize();
        auto t = 0.5 * (unitDirection.y + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
}

int main() {
    // Image dimensions
    std::cout << "Preparing ray tracer... " << std::endl;
    const auto aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = static_cast<int>(width / aspect_ratio);

    // Camera position and orientation
    Vec3 cameraDirection(0, 0, -1);
    Vec3 cameraUp(0, 1, 0);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    Vec3 origin(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);


    // Render the scene
    std::vector<Color> pixels(width * height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            auto x = double(i) / (width + 1);
            auto y = double(j) / (height + 1);

            Ray ray(origin, lower_left_corner + x * horizontal + y * vertical - origin);

#if RAYTRACER
            {
                pixels[j * width + i] = rayColor(ray);

            }
#endif

        }
    }
    // Output the image in PPM format
    std::ofstream outfile("output.ppm");
    outfile << "P3\n" << width << " " << height << "\n255\n";
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color pixel = pixels[j * width + i];
            int r = (int)(255 * clamp(pixel.r, 0, 1));
            int g = (int)(255 * clamp(pixel.g, 0, 1));
            int b = (int)(255 * clamp(pixel.b, 0, 1));
            outfile << r << " " << g << " " << b << " ";
        }
        outfile << "\n";
    }

    return 0;
}
