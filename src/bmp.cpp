#include "bmp.h"

Canva::Canva() :_height(1), _width(1)
{
	pixels = new Pixel * [_height];
	for (int i = 0; i < _height; i++)
		pixels[i] = new Pixel[_width];
}

Canva::Canva(const unsigned int h, const unsigned int w) :_height(h), _width(w)
{
	pixels = new Pixel * [_height];
	for (int i = 0; i < _height; i++)
		pixels[i] = new Pixel[_width];
}


void Canva::setpixel(unsigned int x, unsigned int y, const Pixel&& p)
{
	pixels[y][x].red = p.red;
	pixels[y][x].green = p.green;
	pixels[y][x].blue = p.blue;
}

void Canva::savetofile(const std::string& file_path)
{
	FileHeader file_header;
	InfoHeader info_header;

	info_header.size = sizeof(InfoHeader);
	info_header.width = _width;
	info_header.height = _height;
	info_header.bitcount = 24;
	info_header.size_image = _width * _height * 3;
	info_header.compression = 0;

	file_header.file_size = sizeof(FileHeader) + sizeof(InfoHeader) + info_header.size_image;
	file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader);

	std::ofstream file;
	file.open(file_path, std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "File Error!" << std::endl;
		return;
	}

	file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
	file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));


	//  Ğ´ÈëÏñËØÊı¾İ
	float epsilon = 0.001f;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			//std::cout << pixels[y][x].red << ' ' << pixels[y][x].green << ' ' << pixels[y][x].blue << std::endl;

			auto pixel1 = uint8_t((fabs(pixels[y][x].blue - 1) < epsilon ? 1.f : fabs(pixels[y][x].blue - trunc(pixels[y][x].blue))) * 255.f);
			auto pixel2 = uint8_t((fabs(pixels[y][x].green - 1) < epsilon ? 1.f : fabs(pixels[y][x].green - trunc(pixels[y][x].green))) * 255.f);
			auto pixel3 = uint8_t((fabs(pixels[y][x].red - 1) < epsilon ? 1.f : fabs(pixels[y][x].red - trunc(pixels[y][x].red))) * 255.f);

			//std::cout << fabs(pixels[y][x].blue - trunc(pixels[y][x].blue)) << ' ' << fabs(pixels[y][x].green - trunc(pixels[y][x].green)) << ' ' << fabs(pixels[y][x].red - trunc(pixels[y][x].red)) << std::endl;

			//std::cout << int(pixel1) << ' ' << int(pixel2) << ' ' << int(pixel3) << std::endl;


			uint8_t pix[3] = { pixel1,pixel2,pixel3 };
			file.write(reinterpret_cast<const char*>(pix), 3);
		}
	}

	/*
	// µ¹ÖÃ
	float epsilon = 0.001f;
	for (int y = _height - 1; y >= 0; y--)
	{
		for (int x = _width - 1; x >= 0; x--)
		{
			//std::cout << pixels[y][x].red << ' ' << pixels[y][x].green << ' ' << pixels[y][x].blue << std::endl;

			auto pixel1 = uint8_t((fabs(pixels[y][x].blue - 1) < epsilon ? 1.f : fabs(pixels[y][x].blue - trunc(pixels[y][x].blue))) * 255.f);
			auto pixel2 = uint8_t((fabs(pixels[y][x].green - 1) < epsilon ? 1.f : fabs(pixels[y][x].green - trunc(pixels[y][x].green))) * 255.f);
			auto pixel3 = uint8_t((fabs(pixels[y][x].red - 1) < epsilon ? 1.f : fabs(pixels[y][x].red - trunc(pixels[y][x].red))) * 255.f);

			//std::cout << fabs(pixels[y][x].blue - trunc(pixels[y][x].blue)) << ' ' << fabs(pixels[y][x].green - trunc(pixels[y][x].green)) << ' ' << fabs(pixels[y][x].red - trunc(pixels[y][x].red)) << std::endl;

			//std::cout << int(pixel1) << ' ' << int(pixel2) << ' ' << int(pixel3) << std::endl;


			uint8_t pix[3] = { pixel1,pixel2,pixel3 };
			file.write(reinterpret_cast<const char*>(pix), 3);
		}
	}
	*/
	file.close();
}