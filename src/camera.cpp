#include "camera.h"

Camera::Camera(const initCamera& init) : origin(init.lookfrom)
{
	auto theta = deg2rad(init.vfov);

	auto half_height = tan(theta / 2);
	auto half_width = init.aspect * half_height;

	w = (init.lookfrom - init.lookat).normalized();

	u = init.vup.cross(w).normalized();

	v = w.cross(u);

	lower_left_corner = origin
		- half_width * u
		- half_height * v
		- w;

	horizontal = 2 * half_width * u;
	vertical = 2 * half_height * v;

	aperture = init.aperture / 2;

}


void Camera::get_ray(double s, double t, Ray& r)
{
	//Eigen::Vector3f rd = aperture * random_vec3(-0.7, 0.7);//.normalized();
	//rd = u * rd.x() + v * rd.y();

	r = Ray(origin, (lower_left_corner + s * horizontal + t * vertical - origin).normalized());// - rd);
}
