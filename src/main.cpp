#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"

#include "Hitter.hpp"
#include "HitterList.hpp"
#include "PPMWriter.hpp"
#include "Sphere.hpp"
#include "Utils.hpp"
#include "Constants.hpp"
#include "Camera.hpp"


#define RAYTRACER 1


Color rayColor(const Ray& ray, const HitterList& world) {

    {
        hit_record rec;

        if (world.hit(ray, 0, infinity, rec))
            return 0.5 * Color(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);

        //background
        {
            auto unitDirection = ray.getDirection().normalize();
            auto t = 0.5 * (unitDirection.y + 1.0);
            return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
        }

    }

}

int main() {

    std::cout << "Preparing ray tracer... " << std::endl;



    HitterList world;

    auto s1 = std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5);
    auto s2 = std::make_shared<Sphere>(Vec3(0, -1, -1), 0.9);

    world.add(s1);
    world.add(s2);

    const auto aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = static_cast<int>(width / aspect_ratio);

    auto camera = std::make_unique<Camera>(aspect_ratio);


    // Render the scene
    std::vector<Color> pixels(width * height);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            auto x = double(i) / (width + 1);
            auto y = double(j) / (height + 1);

            Ray ray = camera->getRay(x,y);
#if RAYTRACER
            {
                pixels[j * width + i] = rayColor(ray, world);

            }
#endif

        }
    }

    auto writer = std::make_unique<PPMWriter>(width, height);
    writer->WriteFile(pixels);

    return 0;
}
