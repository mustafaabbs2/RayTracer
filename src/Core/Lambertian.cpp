#include "Lambertian.hpp"

Lambertian::Lambertian(const Color& col)
	: _albedo(col){};

bool Lambertian::scatter(const Ray& ray,
						 const Hit::hit_record& rec,
						 Color& attenuation,
						 Ray& scattered) const
{

	return true;
}