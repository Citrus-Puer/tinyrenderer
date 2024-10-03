#include "hittable.h"

void HitRecord::set_face_normal(const Ray& r, const Eigen::Vector3f& outward_normal)
{
	// 设置碰撞法向
	front_face = (r.direction().dot(outward_normal) < 0);

	normal = front_face ? outward_normal : -outward_normal;
}

bool HitableList::hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const
{
	HitRecord temp_rec;
	//bool hit_anything = false;
	double closest_so_far = ray_tmax;

	// 找到最近的反射光的物体
	for (const auto& object : objects)
	{
		if (object->hit(r, ray_tmin, closest_so_far, temp_rec))
		{
			temp_rec.hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return rec.hit_anything;
}


