#include "spheer.h"

Spheer::Spheer(const Eigen::Vector3f& ce, double r, std::shared_ptr<Material>&& mat) : center(ce), radius(r), mat_ptr(mat) { }

bool Spheer::hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const
{

	Eigen::Vector3f oc = center - r.origin();

	float a = pow(r.direction().norm(), 2);
	float h = r.direction().dot(oc);
	float c = pow(oc.norm(), 2) - radius * radius;
	float discriminant = h * h - a * c;

	if (discriminant < 0)
		return false;

	double sqrtd = sqrt(discriminant);

	double root = (h - sqrtd) / a;

	if (root < ray_tmin || root > ray_tmax)
	{
		root = (h + sqrtd) / a;

		if (root < ray_tmin || root > ray_tmax)
			return false;
	}
	rec.t = root;
	rec.p = r.at(rec.t);

	rec.set_face_normal(r, (rec.p - center).normalized());

	rec.mat_ptr = this->mat_ptr;

	return true;
}