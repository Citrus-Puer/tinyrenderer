#pragma once
#include "GLOBAL.h"
#include "hittable.h"

struct initCamera {

	Eigen::Vector3f lookfrom;
	Eigen::Vector3f lookat;
	Eigen::Vector3f vup;


	double vfov;	// ��ֱ�ӳ��Ƕ�
	double aspect;	// ��߱�

	double focus_dist;
	double aperture;

};


class Camera {

	Eigen::Vector3f origin;	// ���λ��
	Eigen::Vector3f lower_left_corner;	// ���½�����
	Eigen::Vector3f horizontal;	// ÿһ�����������ˮƽ����
	Eigen::Vector3f vertical;	// ÿһ�������������ֱ����

	Eigen::Vector3f u, v, w;

	double focus_dist;
	double aperture;

public:
	Camera();
	Camera(const initCamera& init);



	void get_ray(double s, double v, Ray& r);
};


