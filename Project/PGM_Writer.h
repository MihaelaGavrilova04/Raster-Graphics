#pragma once
#include "ImageWriter.h"
class PGM_Writer:public ImageWriter
{
public:
	PGM_Writer(const char* filepath, const Image* image);
	PGM_Writer(const myString& filepath, const Image* image);

	void saveImage()override;
};