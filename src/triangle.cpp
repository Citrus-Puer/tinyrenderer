#include "triangle.h"


Triangle::Triangle() :_p1(Eigen::Vector3f(0, 0, 0)), _p2(Eigen::Vector3f(0, 0, 0)), _p3(Eigen::Vector3f(0, 0, 0)) {}

Triangle::Triangle(Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3) : _p1(p1), _p2(p2), _p3(p3) {}

bool Triangle::hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const
{
	return false;
}