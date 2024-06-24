#pragma once
#include "RGB.h"
#include "Image.h"
typedef void (*colorConverter)(int, int, RGB&);

class ImageConverter 
{
public:
	ImageConverter() = default;
	virtual ~ImageConverter() = default;
protected:
	virtual void operate(int, int, RGB&) = 0;
	
	//formula which converts RGB to the corresponding gray patterns
	static constexpr double redCoeff = 0.299;
	static constexpr double greenCoeff = 0.587;
	static constexpr double blueCoeff = 0.114;
	static void colorToGray(RGB& pixel);
};