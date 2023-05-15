#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "Camera.hpp"
#include "Color.hpp"
#include "Constants.hpp"
#include "Hitter.hpp"
#include "HitterList.hpp"
#include "Logger.hpp"
#include "PNGWriter.hpp"
#include "PPMWriter.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Sphere.hpp"
#include "Utils.hpp"

#include "ThreadPool.hpp"

#define PARALLEL 1

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

	Camera cam = Camera(aspect_ratio);
	//antialiasing
	const int samplesPerPixel = 10;

	auto writer = std::make_unique<PPMWriter>("new-image2.ppm", width, height);
	// auto writer = std::make_unique<PNGWriter>("new-image2.png", width, height);

#if PARALLEL
	ThreadPool threadPool(2);
#endif
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
				{ //section that should be parallelized - s is run 200+ times
#if PARALLEL
					// parallel
					WorkItem item{i, j, s, x, y, cumulativeColor, cam, world};
					threadPool.addWorkItem(item);
#else
					// serial
					addRayColor(x, y, cumulativeColor, cam, world, maxDepth);
#endif
				}
			}

			writer->WritePixelsToBuffer(cumulativeColor, samplesPerPixel);
		}
	}

	writer->WriteToFile();

	logger->endTimer();

	return 0;
}
