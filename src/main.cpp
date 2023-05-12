#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "Color.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

#include "Camera.hpp"
#include "Constants.hpp"
#include "Hitter.hpp"
#include "HitterList.hpp"
#include "Logger.hpp"
#include "PPMWriter.hpp"
#include "Sphere.hpp"
#include "Utils.hpp"

#include "Lambertian.hpp"
#include "Metal.hpp"

//Note: the headers currently contain definitions too, they need to be put in their own source files to avoid high compilation times on changes

#define WRITE 1

Color rayColor(const Ray& ray, const HitterList& world, int depth)
{

	Hit::hit_record rec;

	if(depth <= 0)
		return Color(0, 0, 0);

	if(world.hit(ray, 0, infinity, rec))
	{
		Ray scattered;
		Color attenuation;
		if(rec.matptr->scatter(ray, rec, attenuation, scattered))
			return attenuation * rayColor(scattered, world, depth - 1);

		Vec3 target = rec.p + rec.normal + randomUnitVector();
		return 0.5 * rayColor(Ray(rec.p, target - rec.p), world, depth - 1); //absorb half
	}
	//background
	{
		auto unitDirection = ray.getDirection().normalize();
		auto t = 0.5 * (unitDirection.y + 1.0);
		return (1.0 - t) * Color(1.0, 1.0, 1.0) +
			   t * Color(0.5, 0.7, 1.0); //gradient from white to blue
	}
}

int main()
{

	HitterList world;

	auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.8));
	auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
	auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
	auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

	auto s1 = std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5, material_center);
	auto s2 = std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100, material_ground);
	auto s3 = std::make_shared<Sphere>(Vec3(-1, 0, -1), 0.5, material_left);
	auto s4 = std::make_shared<Sphere>(Vec3(1, 0, -1), 0.5, material_right);

	world.add(s1);
	world.add(s2);
	world.add(s3);
	world.add(s4);

	const auto aspect_ratio = 16.0 / 9.0;
	const int width = 400;
	const int height = static_cast<int>(width / aspect_ratio);

	const int maxDepth = 50; //ray recursion

	auto logger = std::make_unique<Logger<ConsoleOutput>>();

	auto camera = std::make_unique<Camera>(aspect_ratio);
	//antialiasing
	const int samplesPerPixel = 100;

	auto writer = std::make_unique<PPMWriter>("new.ppm", width, height);

	logger->log("Image generation");
	logger->startTimer();

	for(size_t j = height; j > 0; --j)
	{
		for(size_t i = 0; i < width; ++i)
		{
			Color cumulativeColor(0, 0, 0);
			for(size_t s = 0; s < samplesPerPixel; ++s)
			{
				auto x = double(i + random_double()) / (width - 1);
				auto y = double(j + random_double()) / (height - 1);
#if WRITE
				{
					Ray ray = camera->getRay(x, y);
					cumulativeColor = cumulativeColor + rayColor(ray, world, maxDepth);
				}
			}

			writer->WritePixelToFile(cumulativeColor, samplesPerPixel);
#endif
		}
	}

	logger->endTimer();

	return 0;
}
