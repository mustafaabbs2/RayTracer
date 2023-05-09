#pragma once

#include "Hitter.hpp"

#include <memory>
#include <vector>


//List of hitter objects
class HitterList : public Hitter {

public:

	HitterList() {}
	HitterList(std::shared_ptr<Hitter> object)
	{
		add(object);
	}

	void add(std::shared_ptr<Hitter> object)
	{
		objects.push_back(object);
	}

	void clear()
	{
		objects.clear();
	}


	bool hit(const Ray& ray, double tmin, double tmax, hit_record& rec) const override;

private:
	std::vector<std::shared_ptr<Hitter>> objects;

};

bool HitterList::hit(const Ray& ray, double tmin, double tmax, hit_record& rec) const {

	bool hitAnything = false;
	auto closestT = tmax;
	hit_record temp_rec;
	
	for (const auto& object : objects)
	{

		if (object->hit(ray, tmin, closestT, temp_rec)) //need temp_rec since this may not need to be filled to our final rec unless filled
		{
			hitAnything = true;
			closestT = temp_rec.t;
			rec = temp_rec;
		}


	}

	return hitAnything;


}