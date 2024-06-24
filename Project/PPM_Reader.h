#pragma once
#include "ImageReader.h"
#include <sstream>
#include "RGB.h"
class PPM_Reader : public ImageReader
{
public:
    PPM_Reader(const char* filepath);
    PPM_Reader(const myString& filepath);
private:
    Image* createImage()const override;
};