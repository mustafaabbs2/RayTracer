#pragma once


#include "Vec3.hpp"
#include "Ray.hpp"


//Have a abstract hitter here
//Contains a hit function to check if it got hit..


class Hitter {

public:
	virtual bool hit(const Ray& ray) const = 0; //pure virtual

};

