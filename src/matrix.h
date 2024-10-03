#pragma once
#include <cstdio>
#include <iostream>
#include <Eigen/Dense>


namespace getMatrix {

	const Eigen::Vector3f ROTATION_X(1, 0, 0);
	const Eigen::Vector3f ROTATION_Y(0, 1, 0);
	const Eigen::Vector3f ROTATION_Z(0, 0, 1);

	struct ParaModel {
		float trans_x = 0;
		float trans_y = 0;
		float trans_z = 0;

		Eigen::Vector3f rot_axis = ROTATION_X;
		float angle = 0;

		float scale_x = 0;
		float scale_y = 0;
		float scale_z = 0;
	};


	class Matrix {


	public:
		static Eigen::Matrix4f get_model_matrix(const ParaModel& para);
		static Eigen::Matrix4f get_view_matrix(Eigen::Vector3f position, Eigen::Vector3f target, Eigen::Vector3f up);
		static Eigen::Matrix4f get_projection_matrix(float fov, float aspect, float near, float far);
	};
}
