#pragma once

#include "material.h"
#include "GLOBAL.h"

class Material;

class HitRecord {

public:
	Eigen::Vector3f p;	// 碰撞点
	Eigen::Vector3f normal;	//碰撞表面的法向量
	double t;	// 对应光的t

	std::shared_ptr<Material> mat_ptr;

	bool front_face;
	bool hit_anything;

	void set_face_normal(const Ray& r, const Eigen::Vector3f& outward_normal);
	static Eigen::Vector3f random_in_unit_spheer()
	{
		while (true) {
			auto p = random_vec3(-1, 1);
			if (p.norm() >= 1 || p.norm() < 1e-100) continue;
			return p;
		}
	}


};

class Hittable {

public:
	virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const
	{
		return false;
	}

	~Hittable() {}
};


// 一些可发射光的物体集合
class HitableList :public Hittable {

	std::vector<std::shared_ptr<Hittable>> objects;

public:


	//HitableList() {}
	HitableList(std::shared_ptr<Hittable>&& object) { objects.push_back(object); }

	void clear() { objects.clear(); }
	void add(const std::shared_ptr<Hittable>& object) { objects.push_back(object); }
	void add(std::shared_ptr<Hittable>& object) { objects.push_back(object); }
	bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override;
};

