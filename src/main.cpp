#include "GLOBAL.h"
#include "hittable.h"
#include "matrix.h"
#include "rayTracer.h"
#include "rasterizer.h"
#include "spheer.h"

Pixel common_fragment_shader(const Ray& r, const HitRecord& rec)
{
	//if (rec.hit_anything)
	{
		//auto color1 = (Pixel(1, 1, 1) + rec.normal) * 255 * 0.5;
	//	return (Pixel(127, 127, 127) + rec.normal * 127.5);
	}
	float a = 0.5 * (r.direction().normalized().y() + 1.);

	auto color = Pixel(1.f, 1.f, 1.f) * (1.0 - a) + Pixel(0.5f, 0.7f, 1.f) * a;

	return color;
}

int main()
{



	initCamera initC;
	initC.aspect_ratio = 16. / 9.;
	initC.focal_length = 1;
	initC.image_width = 400;
	initC.viewport_height = 2;
	initC.center = Eigen::Vector3f(0., 0., 1.);

	std::function<Pixel(const Ray&, const HitRecord&)> func = common_fragment_shader;


	RayTracer rt(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(0, 0, -1.2), 0.5, std::make_shared<Lambertian>(Eigen::Vector3f(0.5f, 0.5f, 0.5f)))), initC, func);

	rt.add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(0, -100.5, -1), 100, std::make_shared<Lambertian>(Eigen::Vector3f(0.5f, 0.5f, 0.5f)))));
	rt.add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(1, 0, -1), 0.5, std::make_shared<Metal>(Eigen::Vector3f(0.8f, 0.6f, 0.2f), 0.f))));
	//rt.add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(-1, 0, -1), -0.45, std::make_shared<Dielectrics>(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 1.5f))));
	rt.add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(-1, 0, -1), 0.5, std::make_shared<Metal>(Eigen::Vector3f(0.8f, 0.5f, 0.5f), 0.3f))));

	//rt.setAntiAliasLevel(AntiAliasLevel::SSAA3X);

	rt.render();

	return 0;
}

