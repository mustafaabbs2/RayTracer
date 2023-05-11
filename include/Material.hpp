#pragma once

#include "Ray.hpp"
#include "Hitter.hpp"
#include "Color.hpp"

class Material {

public:
	virtual bool scatter(const Ray& ray, const hit_record& rec, Color& attenuation, Ray& scattered) const = 0;

};