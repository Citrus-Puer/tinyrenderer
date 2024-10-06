#pragma once
#include "GLOBAL.h"
#include "camera.h"

enum AntiAliasLevel {
	NONE = 0,
	BLUR = 1,
	SSAA2X = 2,
	SSAA3X = 3,
	MSAA2X = 4
};

class RayTracer {

	static RayTracer* raytracer;

	Camera cam;
	Canva img;
	HitableList scene;

	uint8_t num_sample_rays = 100;
	std::function<Pixel(const Ray&, const HitRecord&)> fragment_shader_payload;

	AntiAliasLevel anti = AntiAliasLevel::NONE;

	Pixel fragment_shader(const Ray& r, int depth);
	void vertex_shader();
	uint8_t max_depth = 10;

	RayTracer();
	RayTracer(const initCamera& c, std::function<Pixel(const Ray&, const HitRecord&)> func, int height, int width);


public:

	static RayTracer* getInstance(const initCamera& c, std::function<Pixel(const Ray&, const HitRecord&)> func, int height, int width) {
		if (!raytracer)
			raytracer = new RayTracer(c, func, height, width);
		return raytracer;
	}

	void render();


	void render_with_threads(int num);
	void render_for_each_thread(int begin, int end);

	void add(const std::shared_ptr<Hittable>& obj);
	void add(std::shared_ptr<Hittable>&& obj);


	void setAntiAliasLevel(AntiAliasLevel a) { anti = a; }
};

