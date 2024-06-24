#pragma once
#include "ImageConverter.h"
#include "RGB.h"
#include "Image.h"
class NegativeConverter :public ImageConverter
{
public:
	NegativeConverter() = default;
	void toNegative(Image * image);
private:
	void operate(int x, int y, RGB& pixel)override;
};