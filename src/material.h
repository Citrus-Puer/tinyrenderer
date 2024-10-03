#pragma once
#include "GLOBAL.h"
#include "hittable.h"


class HitRecord;

Eigen::Vector3f reflect(const Eigen::Vector3f& inDirection, const Eigen::Vector3f& normal);
Eigen::Vector3f refract(const Eigen::Vector3f& inDirection, const Eigen::Vector3f& normal, float index);
double schlick(double cosine, double index);

class Material {

public:
	virtual ~Material() = default;

	virtual bool scatter(
		const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attenuation, Ray& scattered
	)const {
		return false;
	}
};




class Lambertian : public Material {
	Eigen::Vector3f albedo;
public:
	Lambertian(const Eigen::Vector3f& albedo) :albedo(albedo) {}

	bool scatter(
		const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attenuation, Ray& scattered
	)const override;

};



class Metal : public Material {
	float fuzz;
	Eigen::Vector3f albedo;
public:
	Metal(const Eigen::Vector3f& albedo, float f) :albedo(albedo), fuzz(f) {}

	bool scatter(
		const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attenuation, Ray& scattered
	)const override;
};

class Dielectrics : public Material {
	Eigen::Vector3f albedo;
	float index;

public:

	Dielectrics(const Eigen::Vector3f& albedo, float ind) : albedo(albedo), index(ind) {}

	bool scatter(
		const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attenuation, Ray& scattered
	)const override;

};



