#pragma once
#include <memory>
#include <limits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <functional>
#include <random>


const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;



#include "interval.h"
#include "bmp.h"
#include "ray.h"
#include <Eigen/Dense>

inline double deg2rad(double degree)
{
	return degree * pi / 180.;
}

inline double random_double()
{
	return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	return min + (max - min) * random_double();
}



inline Eigen::Vector3f random_vec3()
{
	return Eigen::Vector3f(random_double(), random_double(), random_double());
}

inline Eigen::Vector3f random_vec3(double min, double max)
{
	return Eigen::Vector3f(random_double(min, max), random_double(min, max), random_double(min, max));
}