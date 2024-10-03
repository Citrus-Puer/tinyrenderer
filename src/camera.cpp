#include "camera.h"

Camera::Camera()
	:_aspect_ratio(0.), _image_width(0.), _center(Eigen::Vector3f(0., 0., 0.))
{

}

Camera::Camera(const initCamera& init)
	: _center(init.center) {
	_aspect_ratio = init.aspect_ratio;
	_image_width = init.image_width;
	_focal_length = init.focal_length;
	_viewport_height = init.viewport_height;
}

Camera::Camera(double ratio = 1., int width = 0, Eigen::Vector3f ct = Eigen::Vector3f(0., 0., 0.))
	: _aspect_ratio(ratio), _image_width(ratio), _center(ct)
{

}