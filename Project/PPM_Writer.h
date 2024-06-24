#pragma once
#include "ImageWriter.h"
class PPM_Writer :public ImageWriter
{
public:
	PPM_Writer(const char* filepath, const Image* image);
	PPM_Writer(const myString& filepath, const Image* image);

	void saveImage()override;
};