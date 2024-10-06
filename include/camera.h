#pragma once
#include "GLOBAL.h"
#include "hittable.h"

struct initCamera {

	Eigen::Vector3f lookfrom;
	Eigen::Vector3f lookat;
	Eigen::Vector3f vup;


	double vfov;	// 垂直视场角度
	double aspect;	// 宽高比

	double focus_dist;
	double aperture;

};


class Camera {

	Eigen::Vector3f origin;	// 相机位置
	Eigen::Vector3f lower_left_corner;	// 左下角坐标
	Eigen::Vector3f horizontal;	// 每一个像素坐标的水平分量
	Eigen::Vector3f vertical;	// 每一个像素坐标的竖直分量

	Eigen::Vector3f u, v, w;

	double focus_dist;
	double aperture;

public:
	Camera();
	Camera(const initCamera& init);



	void get_ray(double s, double v, Ray& r);
};


