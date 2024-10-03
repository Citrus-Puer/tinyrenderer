#pragma once
#include <Eigen/Dense>
class Ray
{
	Eigen::Vector3f orig;
	Eigen::Vector3f dir;

public:
	Ray();
	Ray(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction);
	Eigen::Vector3f at(double t) const;
	Eigen::Vector3f direction() const { return dir; }
	Eigen::Vector3f origin() const { return orig; };

};