#pragma once
#include "ImageConverter.h"
#include "Image.h"
class GrayscaleConverter : public ImageConverter
{
public:
    GrayscaleConverter() = default;
	void toGrayscale(Image* image);
private:
	void operate(int x, int y, RGB& pixel)override;
};