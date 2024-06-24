#pragma once
#include "Image.h"
#include "myString.h"

class ImageWriter
{
protected:
	std::ofstream writeStream;
	const Image* image;

	ImageWriter(const char* filepath,const Image* image);
	ImageWriter(const myString& filepath,const Image* image);
public:
	virtual void saveImage() = 0;
	virtual ~ImageWriter();
};