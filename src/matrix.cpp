#include "matrix.h"
#include <cmath>

namespace getMatrix {
	Eigen::Matrix4f Matrix::get_model_matrix(const ParaModel& para)
	{
		Eigen::Matrix4f translation, rotation, scaling;

		// 平移矩阵
		translation << 1, 0, 0, para.trans_x,
			0, 1, 0, para.trans_y,
			0, 0, 1, para.trans_z,
			0, 0, 0, 1;

		// 旋转矩阵

		float cosa = cos(para.angle), sina = sin(para.angle);

		auto& N = para.rot_axis;

		rotation <<
			cosa + float(pow(N.x(), 2)) * (1.f - cosa), N.x()* N.y()* (1.f - cosa) - N.z() * sina, N.x()* N.z()* (1 - cosa) + N.y() * sina, 0,
			N.y()* N.x()* (1 - cosa) + N.z() * sina, cosa + float(pow(N.y(), 2)) * (1.f - cosa), N.y()* N.z()* (1.f - cosa) - N.x() * sina, 0,
			N.z()* N.x()* (1 - cosa) + N.y() * sina, N.z()* N.y()* (1.f - cosa) - N.x() * sina, cosa + float(pow(N.z(), 2)) * (1.f - cosa), 0,
			0, 0, 0, 1;


		// 缩放矩阵
		scaling << para.scale_x, 0, 0, 0,
			0, para.scale_y, 0, 0,
			0, 0, para.scale_z, 0,
			0, 0, 0, 1;

		return translation * rotation * scaling;

	}
	Eigen::Matrix4f Matrix::get_view_matrix(Eigen::Vector3f position, Eigen::Vector3f target, Eigen::Vector3f up)
	{
		Eigen::Vector3f F = (target - position).normalized();

		Eigen::Vector3f R = F.cross(up).normalized();

		Eigen::Vector3f U = R.cross(F);


		Eigen::Matrix4f viewMatrix;

		viewMatrix << R.x(), R.y(), R.z(), -R.dot(position),
			U.x(), U.y(), U.z(), -U.dot(position),
			-F.x(), -F.y(), -F.z(), F.dot(position),
			0, 0, 0, 1;

		return viewMatrix;
	}

	/// <summary>
	/// 透视投影矩阵
	/// </summary>
	/// <param name="fov"> 垂直视角 </param>
	/// <param name="aspect"> 宽高比 </param>
	/// <param name="near"> 近平面距离摄像机的距离 </param>
	/// <param name="far"> 远平面距离摄像机的距离 </param>
	Eigen::Matrix4f Matrix::get_projection_matrix(float fov, float aspect, float near, float far)
	{
		Eigen::Matrix4f projection = Eigen::Matrix4f::Zero();
		// 计算投影矩阵的各个元素
		float tanHalfFov = tan(fov / 2.0f);

		projection(0, 0) = 1.0f / (aspect * tanHalfFov);
		projection(1, 1) = 1.0f / tanHalfFov;
		projection(2, 2) = -(far + near) / (far - near);
		projection(2, 3) = -(2.0f * far * near) / (far - near);
		projection(3, 2) = -1.0f;

		return projection;
	}
}


