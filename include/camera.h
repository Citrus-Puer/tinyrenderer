#pragma once
#include "GLOBAL.h"
#include "hittable.h"

struct initCamera {
	double aspect_ratio;
	int image_width;

	double focal_length;
	double viewport_height;
	Eigen::Vector3f center;


	Eigen::Vector3f lookfrom;
	Eigen::Vector3f lookat;
	double vfov;
	double aspect;
	double focus_dist;


};


class Camera {
	double _aspect_ratio;
	int _image_width;
	double _focal_length;
	double _viewport_height;
	Eigen::Vector3f _center;



public:
	Camera();
	Camera(const initCamera& init);
	Camera(double ratio, int width, Eigen::Vector3f ct);
	double aspect_ratio()const { return _aspect_ratio; }
	int image_width() const { return _image_width; }

	double focal_length() const { return _focal_length; }
	double viewport_height() const { return _viewport_height; }

	Eigen::Vector3f center() const { return _center; }

	Ray get_ray(double s, double v);
};

