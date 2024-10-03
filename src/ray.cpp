#include "ray.h"

Ray::Ray() :orig(Eigen::Vector3f(.0, .0, .0)), dir(Eigen::Vector3f(.0, .0, .0)) {}

Ray::Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) : orig(origin), dir(direction) {}

Eigen::Vector3f Ray::at(double t) const {
	return orig + t * dir;
}
