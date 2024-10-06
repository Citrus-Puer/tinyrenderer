#include "rayTracer.h"
#include <Windows.h>

RayTracer* RayTracer::raytracer = nullptr;


RayTracer::RayTracer(const initCamera& ca,
	std::function<Pixel(const Ray&, const HitRecord&)> func, int height, int width)
	: cam(ca), img(height, width), fragment_shader_payload(func)
{
}

void RayTracer::render()
{
	auto image_height = img.height();
	auto image_width = img.width();

	printf("%d  %d\n", image_height, image_width);

	double offset_w = 0.4 / image_width;
	double offset_h = 0.4 / image_height;

	if (anti == AntiAliasLevel::NONE)
	{
		for (int j = 0; j < image_height; j++)
		{
			for (int i = 0; i < image_width; i++)
			{
				Ray r;

				double s = double(i) / image_width;
				double t = double(j) / image_height;

				s += random_double(-offset_w, offset_w);
				t += random_double(-offset_h, offset_h);

				cam.get_ray(s, t, r);


				Pixel color(0.f, 0.f, 0.f);
				for (int i = 0; i < num_sample_rays; i++)
				{
					color = color + fragment_shader(r, 0) * (1. / num_sample_rays);
				}
				img.setpixel(i, j, std::move(color));
			}

			if (j % 10 == 0)
				std::cout << std::endl;
			std::cout << '=';

		}
	}
	std::cout << "=> Finished!" << std::endl;

	if (anti == AntiAliasLevel::BLUR)
	{
		Canva temp(img);
		for (int j = 1; j < image_height - 1; j++)
			for (int i = 1; i < image_width - 1; i++)
				img.setpixel(i, j, temp.at(i, j) * 0.111 + temp.at(i - 1, j) * 0.111 + temp.at(i - 1, j - 1) * 0.111 + temp.at(i + 1, j) * 0.111 + temp.at(i, j + 1) * 0.111 + temp.at(i + 1, j + 1) * 0.111 + temp.at(i + 1, j - 1) * 0.111 + temp.at(i - 1, j + 1) * 0.111 + temp.at(i, j - 1) * 0.111);
	}

	img.savetofile("./img5.bmp");
}

void RayTracer::render_with_threads(int num)
{
	std::vector<std::thread> threads;
	int block = img.height() / num;

	int begin = 0, end = block;

	for (int i = 0; i < num; i++)
	{
		std::thread t(&RayTracer::render_for_each_thread, this, begin, end);

		threads.push_back(std::move(t));

		begin += block;
		end += block;
	}
	for (int i = 0; i < num; i++)
	{
		threads[i].join();
	}
	img.savetofile("./img5.bmp");
}

void RayTracer::render_for_each_thread(int begin, int end)
{
	auto image_height = img.height();
	auto image_width = img.width();

	printf("%d  %d\n", image_height, image_width);

	double offset_w = 0.4 / image_width;
	double offset_h = 0.4 / image_height;

	if (anti == AntiAliasLevel::NONE)
	{
		for (int j = begin; j < end; j++)
		{
			for (int i = 0; i < image_width; i++)
			{
				Ray r;

				double s = double(i) / image_width;
				double t = double(j) / image_height;

				s += random_double(-offset_w, offset_w);
				t += random_double(-offset_h, offset_h);

				cam.get_ray(s, t, r);

				Pixel color(0.f, 0.f, 0.f);
				for (int i = 0; i < num_sample_rays; i++)
				{
					color = color + fragment_shader(r, 0) * (1. / num_sample_rays);
				}
				img.setpixel(i, j, std::move(color));
			}

			if (j % 10 == 0)
				std::cout << std::endl;
			std::cout << '=';
		}
	}
	std::cout << "=> Finished!" << std::endl;
}




Pixel RayTracer::fragment_shader(const Ray& r, int depth)
{
	HitRecord rec;
	rec.hit_anything = false;
	if (depth > max_depth)
		return Pixel(0.f, 0.f, 0.f);


	if (scene.hit(r, 0.001, infinity, rec))	//生成反射子光线,设置最小光线传播距离，忽略过短的反射
	{
		Ray scattered;
		Eigen::Vector3f attenuation; // 吸收率

		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return fragment_shader(scattered, depth + 1) * attenuation;
		}
		return Pixel(0.f, 0.f, 0.f);
	}
	return fragment_shader_payload(r, rec);
}


// 变换顶点坐标
void RayTracer::vertex_shader()
{


}

void RayTracer::add(const std::shared_ptr<Hittable>& obj)
{
	scene.add(obj);
}

void RayTracer::add(std::shared_ptr<Hittable>&& obj)
{
	scene.add(obj);
}

