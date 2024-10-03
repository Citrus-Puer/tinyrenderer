#pragma once
#include "GLOBAL.h"
#include "hittable.h"

class Spheer : public Hittable {

	Eigen::Vector3f center;
	double radius;
	std::shared_ptr<Material> mat_ptr;

public:
	Spheer(const Eigen::Vector3f& ce, double r, std::shared_ptr<Material>&& mat);
	bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;
};