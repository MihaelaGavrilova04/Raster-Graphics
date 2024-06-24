#pragma once
#include "ImageWriter.h"
class PBM_Writer :public ImageWriter
{
public:
	PBM_Writer(const char* filepath, const Image* image);
	PBM_Writer(const myString& filepath, const Image* image);

	void saveImage()override;
private:
	static constexpr int RGB_WHITE = 255;
	static constexpr int RGB_BLACK = 0;

	//white in PBM format is represented in 0 and black - in 1.
	static constexpr int PBM_WHITE = 0;
	static constexpr int PBM_BLACK = 1;
};