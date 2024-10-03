#include "material.h"


Eigen::Vector3f reflect(const Eigen::Vector3f& inDirection, const Eigen::Vector3f& normal)
{
	return inDirection - 2 * normal.dot(inDirection) * normal;
}

Eigen::Vector3f refract(const Eigen::Vector3f& inDirection, const Eigen::Vector3f& normal, float index)
{
	// 入射角
	auto cos_theta = fmin(-inDirection.dot(normal), 1.0);

	// 水平分量
	Eigen::Vector3f r_parallel = index * (inDirection + cos_theta * normal);

	//数值分量
	Eigen::Vector3f r_perp = -sqrt(1.0f - pow(r_parallel.norm(), 2)) * normal;

	return r_parallel + r_perp;
}

// 用于近似折射概率随入射角改变的Christophe Schlick公式
double schlick(double cosine, double index)
{
	auto r0 = (1 - index) / (1 + index);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}


bool Lambertian::scatter(
	const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attenuation, Ray& scattered
) const {
	Eigen::Vector3f scatter_direction = rec.normal + random_vec3(-1, 1).normalized();
	scattered = Ray(rec.p, scatter_direction);
	attenuation = albedo;

	return true;
}




bool Metal::scatter(
	const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attenuation, Ray& scattered
) const {
	Eigen::Vector3f reflected = reflect(r_in.direction(), rec.normal) + (fuzz * random_vec3().normalized());
	scattered = Ray(rec.p, reflected);
	attenuation = albedo;
	return (scattered.direction().dot(rec.normal) > 0);	// 如果投射的光线会回到平面则忽略
}


bool Dielectrics::scatter(
	const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attenuation, Ray& scattered
)const {
	attenuation = albedo;

	float etai = rec.front_face ? 1.0 / index : index;

	float cos_theta = fmin((-r_in.direction()).normalized().dot(rec.normal), 1.0f);
	float sin_theta = sqrt(1.0 - double(cos_theta) * cos_theta);

	if (double(etai) * sin_theta > 1.0)
	{
		Eigen::Vector3f reflected = reflect(r_in.direction().normalized(), rec.normal);
		scattered = Ray(rec.p, reflected);
		return true;
	}


	double reflect_prob = schlick(cos_theta, etai);
	if (random_double() < reflect_prob)
	{
		Eigen::Vector3f reflected = reflect(r_in.direction().normalized(), rec.normal);
		scattered = Ray(rec.p, reflected);
		return true;
	}

	auto refracted = refract(r_in.direction().normalized(), rec.normal, etai);
	scattered = Ray(rec.p, refracted);
	return true;

}