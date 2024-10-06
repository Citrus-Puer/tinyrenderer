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
	uint32_t file_size{ 0 };   // �ļ���С�������ļ�ͷ
	uint16_t reserved1{ 0 };    // ������
	uint16_t reserved2{ 0 };   // ������
	uint32_t offset_data{ 0 }; // �ļ�ͷ��λͼ���ݵ�ƫ���ֽ���
};

struct InfoHeader {
	uint32_t size{ 0 };    // �ṹ�峤��
	int32_t width{ 0 };   // ͼƬ���
	int32_t height{ 0 };  // ͼƬ�߶�
	uint16_t planes{ 1 };  // λƽ����
	uint16_t bitcount{ 0 }; // ��ɫλ��
	uint32_t compression{ 0 }; // �Ƿ�ѹ��
	uint32_t size_image{ 0 };  // λͼ����ʵ��ռ�õ��ֽ���
	int32_t x_ppm{ 0 };    // ˮƽ�ֱ���   ÿ�׵�������
	int32_t y_ppm{ 0 };    // ��ֱ�ֱ��� 
	uint32_t colors_used{ 0 }; // ʵ��ʹ�õ���ɫ��
	uint32_t colors_important{ 0 };    // ��Ҫ����ɫ��
};
#pragma pack(pop)

#endif
