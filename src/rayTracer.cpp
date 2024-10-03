#include "rayTracer.h"
#include <Windows.h>



RayTracer::RayTracer(std::shared_ptr<Hittable>&& h, const initCamera& ca,
	std::function<Pixel(const Ray&, const HitRecord&)> func)
	: cam(ca), img(int(ca.image_width / ca.aspect_ratio), ca.image_width), scene(std::move(h)), fragment_shader_payload(func)
{
}

void RayTracer::render()
{
	// 相机参数

	auto aspect_ratio = cam.aspect_ratio();
	auto image_width = cam.image_width();

	auto focal_length = cam.focal_length();
	auto viewport_height = cam.viewport_height();
	auto camera_center = cam.center();

	int image_height = int(image_width / aspect_ratio);
	image_height = image_height < 1 ? 1 : image_height;

	auto viewport_width = viewport_height * cam.aspect_ratio();//* (float(image_width) / image_height);


	// 计算水平视口边缘和垂直视口边缘的矢量
	auto viewport_u = Eigen::Vector3f(viewport_width, 0, 0);
	auto viewport_v = Eigen::Vector3f(0, -viewport_height, 0);

	// 计算每个像素的水平和垂直增量向量
	Eigen::Vector3f pixel_delta_u = viewport_u / image_width;
	Eigen::Vector3f pixel_delta_v = viewport_v / image_height;

	// 计算左上方像素的位置
	Eigen::Vector3f viewport_upper_left = camera_center - Eigen::Vector3f(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	// 像素(0,0)的位置
	Eigen::Vector3f pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	printf("%d  %d\n", image_height, image_width);


	if (anti == AntiAliasLevel::NONE)
	{
		for (int j = 0; j < image_height; j++)
		{
			for (int i = 0; i < image_width; i++)
			{
				Eigen::Vector3f pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
				// 光线方向
				Eigen::Vector3f ray_direction = pixel_center - camera_center;
				Ray r(camera_center, ray_direction);
				// 调用着色器
				Pixel color(0.f, 0.f, 0.f);
				for (int i = 0; i < num_sample_rays; i++)
				{
					color = color + fragment_shader(r, 0) * (1. / num_sample_rays);
				}
				img.setpixel(i, j, std::move(color));
			}
		}
	}
	/*
	else if (anti == AntiAliasLevel::SSAA2X)
	{
		for (int j = 0; j < image_height; j++)
		{
			for (int i = 0; i < image_width; i++)
			{
				Pixel color(0, 0, 0);
				Eigen::Vector3f pixel = pixel00_loc + ((i - 0.5) * pixel_delta_u) + ((j - 0.5) * pixel_delta_v);

				for (int indy = 0; indy < 2; indy++)
				{
					for (int indx = 0; indx < 2; indx++)
					{
						Eigen::Vector3f px = pixel + indy * pixel_delta_u + indx * pixel_delta_v;
						Eigen::Vector3f ray_direction = px - camera_center;
						Ray r(camera_center, ray_direction);

						color = color + fragment_shader(r) * 0.25;
					}
				}
				img.setpixel(i, j, std::move(color));
			}
		}
	}
	else if (anti == AntiAliasLevel::SSAA3X)
	{
		for (int j = 0; j < image_height; j++)
		{
			for (int i = 0; i < image_width; i++)
			{
				Pixel color(0, 0, 0);
				Eigen::Vector3f pixel = pixel00_loc + ((i - 0.33333) * pixel_delta_u) + ((j - 0.33333) * pixel_delta_v);

				for (int indy = 0; indy < 3; indy++)
				{
					for (int indx = 0; indx < 3; indx++)
					{
						Eigen::Vector3f px = pixel + indy * pixel_delta_u * 0.33333 + indx * pixel_delta_v * 0.33333;
						Eigen::Vector3f ray_direction = px - camera_center;
						Ray r(camera_center, ray_direction);

						color = color + fragment_shader(r) * 0.11111;
					}
				}
				color = color;
				img.setpixel(i, j, std::move(color));
			}
		}
	}
	else if (anti == AntiAliasLevel::MSAA2X)
	{

	}

	if (anti == AntiAliasLevel::BLUR)
	{
		Canva temp(img);
		for (int j = 1; j < image_height - 1; j++)
			for (int i = 1; i < image_width - 1; i++)
				img.setpixel(i, j, temp.at(i, j) * 0.111 + temp.at(i - 1, j) * 0.111 + temp.at(i - 1, j - 1) * 0.111 + temp.at(i + 1, j) * 0.111 + temp.at(i, j + 1) * 0.111 + temp.at(i + 1, j + 1) * 0.111 + temp.at(i + 1, j - 1) * 0.111 + temp.at(i - 1, j + 1) * 0.111 + temp.at(i, j - 1) * 0.111);
	}
	*/
	img.savetofile("./img5.bmp");
}

Pixel RayTracer::fragment_shader(const Ray& r, int depth)
{
	HitRecord rec;
	rec.hit_anything = false;
	if (depth > max_depth)
		return Pixel(0.f, 0.f, 0.f);


	if (scene.hit(r, 0.0001, infinity, rec))	//生成反射子光线,设置最小光线传播距离，忽略过短的反射
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

