#pragma once
#include "ImageReader.h"
#include <sstream>

class PBM_Reader:public ImageReader
{
public:
	PBM_Reader(const char* filename);
	PBM_Reader(const myString& filename);
private:
	Image* createImage()const override;
	
	static constexpr int WHITE = 1;
	const unsigned int BLACK = 0;
};