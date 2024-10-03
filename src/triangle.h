#pragma once
#include "GLOBAL.h"
#include "hittable.h"


class Triangle :public Hittable {
	Eigen::Vector3f _p1, _p2, _p3;
public:

	Triangle();
	Triangle(Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3);
	bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;

};
