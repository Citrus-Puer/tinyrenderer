#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <fstream>
#include <Eigen/Dense>

struct Pixel {
	float red;
	float green;
	float blue;
	Pixel() :red(0.f), green(0.f), blue(0.f) {}
	Pixel(float r, float g, float b) : red(r), green(g), blue(b) {}
	Pixel(uint8_t r, uint8_t g, uint8_t b) : red(r / 255.f), green(g / 255.f), blue(b / 255.f) {}
	Pixel(const Eigen::Vector3f& vec)
	{
		red = vec.x();
		blue = vec.y();
		green = vec.z();
	}

	Pixel operator*(const float& i) { return Pixel(i * red, i * green, i * blue); }

	Pixel operator*(const Eigen::Vector3f& v) { return Pixel(v.x() * red, v.y() * green, v.z() * blue); }

	Pixel operator+(const Pixel& o) { return Pixel(o.red + red, o.green + green, o.blue + blue); }

	Pixel operator+(const Eigen::Vector3f& o) { return Pixel(o.x() + red, o.y() + green, o.z() + blue); }

};

class Canva {

	Pixel** pixels;
	unsigned int _height, _width;

public:
	Canva();
	Canva(const unsigned int height, const unsigned int width);
	~Canva()
	{
		for (int i = 0; i < _height; i++)
		{
			delete[] pixels[i];
		}
		delete[]pixels;
	}

	void setpixel(unsigned int x, unsigned int y, const Pixel&& p);
	void savetofile(const std::string& file_path);
	Pixel at(int i, int j) { return pixels[j][i]; }


	unsigned int height() const { return _height; }
	unsigned int width() const { return _width; }

};

#pragma pack(push,1)
struct FileHeader {
	uint16_t file_type{ 0x4D42 };   // "BM"
	uint32_t file_size{ 0 };   // 文件大小，包括文件头
	uint16_t reserved1{ 0 };    // 保留字
	uint16_t reserved2{ 0 };   // 保留字
	uint32_t offset_data{ 0 }; // 文件头到位图数据的偏移字节数
};

struct InfoHeader {
	uint32_t size{ 0 };    // 结构体长度
	int32_t width{ 0 };   // 图片宽度
	int32_t height{ 0 };  // 图片高度
	uint16_t planes{ 1 };  // 位平面数
	uint16_t bitcount{ 0 }; // 颜色位数
	uint32_t compression{ 0 }; // 是否压缩
	uint32_t size_image{ 0 };  // 位图数据实际占用的字节数
	int32_t x_ppm{ 0 };    // 水平分辨率   每米的像素数
	int32_t y_ppm{ 0 };    // 竖直分辨率 
	uint32_t colors_used{ 0 }; // 实际使用的颜色数
	uint32_t colors_important{ 0 };    // 重要的颜色数
};
#pragma pack(pop)

#endif
