#include "GLOBAL.h"
#include "hittable.h"
#include "matrix.h"
#include "rayTracer.h"
#include "rasterizer.h"
#include "spheer.h"

Pixel common_fragment_shader(const Ray& r, const HitRecord& rec)
{

	float a = 0.5 * (r.direction().normalized().y() + 1.);

	auto color = Pixel(1.f, 1.f, 1.f) * (1.0 - a) + Pixel(0.5f, 0.7f, 1.f) * a;

	return color;
}

int main()
{
	initCamera initC;

	int img_height = 1080, img_width = 1920;

	initC.aspect = double(img_width) / img_height;
	initC.lookat = Eigen::Vector3f(0, 0, 0);
	initC.lookfrom = Eigen::Vector3f(13, 2, 3);
	initC.vfov = 20;
	initC.vup = Eigen::Vector3f(0, 1, 0);
	initC.focus_dist = 10.0;
	initC.aperture = 0.1;


	std::function<Pixel(const Ray&, const HitRecord&)> func = common_fragment_shader;


	RayTracer* rt = RayTracer::getInstance(initC, func, img_height, img_width);


	rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(0, -1000, 0), 1000, std::make_shared<Lambertian>(Eigen::Vector3f(0.5f, 0.5f, 0.5f)))));

	int i = 1;
	for (int a = -11; a < 11; a += 1)
	{
		for (int b = -11; b < 11; b += 1)
		{
			auto choose_mat = random_double();
			Eigen::Vector3f center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - Eigen::Vector3f(4, 0.2, 0)).norm() > 0.9)
			{
				if (choose_mat < 0.8)
				{
					auto albedo = random_vec3(0.2, 1.0);
					rt->add(std::make_shared<Spheer>(center, 0.2, std::make_shared<Lambertian>(albedo)));
				}
				else if (choose_mat < 0.95)
				{
					auto albedo = random_vec3(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					rt->add(std::make_shared<Spheer>(center, 0.2, std::make_shared<Metal>(albedo, fuzz)));
				}
				else
					rt->add(std::make_shared<Spheer>(center, 0.2, std::make_shared<Dielectrics>(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 1.5f)));
			}
		}
	}

	rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(0, 1, 0), 1.0, std::make_shared<Dielectrics>(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 1.5f))));

	rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(-4, 1, 0), 1.0, std::make_shared<Lambertian>(Eigen::Vector3f(0.4f, 0.2f, 0.1f)))));
	rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(4, 1, 0), 1.0, std::make_shared<Metal>(Eigen::Vector3f(0.7f, 0.6f, 0.5f), 0.f))));

	//rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(0, 0, -1), 0.5, std::make_shared<Lambertian>(Eigen::Vector3f(0.5f, 0.5f, 0.5f)))));
	//rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(0, -100.5, -1), 100, std::make_shared<Lambertian>(Eigen::Vector3f(0.5f, 0.5f, 0.5f)))));
	//rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(1, 0, -1), 0.5, std::make_shared<Metal>(Eigen::Vector3f(0.8f, 0.6f, 0.2f), 0.f))));
	//rt->add(std::make_shared<Spheer>(Spheer(Eigen::Vector3f(-1, 0, -1), 0.5, std::make_shared<Dielectrics>(Eigen::Vector3f(1.0f, 1.0f, 1.0f), 1.5f))));


	//rt->render();

	rt->render_with_threads(8);

	return 0;
}

