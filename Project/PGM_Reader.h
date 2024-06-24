#pragma once
#include "ImageReader.h"
#include <sstream>
class PGM_Reader:public ImageReader
{
public:
	PGM_Reader(const char* filepath);
	PGM_Reader(const myString& filepath);
private:
	Image* createImage() const override;
};