#include "PPM_Writer.h"

PPM_Writer::PPM_Writer(const char* filepath, const Image* image) :ImageWriter(filepath, image) {}
PPM_Writer::PPM_Writer(const myString& filepath, const Image* image) :ImageWriter(filepath, image) {}
void PPM_Writer::saveImage()
{
	int width = image->getWidth();
	int height = image->getHeight();
	int maxValue = image->getMaxValue();

	writeStream << "P3" << '\n';
	writeStream << width << " " << height << '\n';
	writeStream << maxValue << '\n';

	int imageGridSize = width * height;
	for (int i = 0; i < imageGridSize; i++)
	{
		if (i == width - 1)
			writeStream << '\n';
		writeStream << (*image)[i] << ' ';
	}
}