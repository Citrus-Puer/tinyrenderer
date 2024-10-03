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
	Camera cam;
	Canva img;
	HitableList scene;

	uint8_t num_sample_rays = 10;
	std::function<Pixel(const Ray&, const HitRecord&)> fragment_shader_payload;

	AntiAliasLevel anti = AntiAliasLevel::NONE;

	Pixel fragment_shader(const Ray& r, int depth);
	void vertex_shader();
	uint8_t max_depth = 5;


public:
	RayTracer();
	RayTracer(std::shared_ptr<Hittable>&& h, const initCamera& c, std::function<Pixel(const Ray&, const HitRecord&)> func);

	void render();

	void add(const std::shared_ptr<Hittable>& obj);
	void add(std::shared_ptr<Hittable>&& obj);

	void setAntiAliasLevel(AntiAliasLevel a) { anti = a; }
};

