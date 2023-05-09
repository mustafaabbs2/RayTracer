#pragma once


#include "Vec3.hpp"
#include "Ray.hpp"


//Details about where the ray intersected the geometry
struct hit_record {

	Vec3 p;
	Vec3 normal;
	double t;

};

//Contains a hit function to check if it got hit..

class Hitter {

public:
	virtual bool hit(const Ray& ray, double tmin, double tmax, hit_record& rec) const = 0; //pure virtual

};

