#include "PBM_Writer.h"

PBM_Writer::PBM_Writer(const char* filepath, const Image* image) :ImageWriter(filepath, image) {}
PBM_Writer::PBM_Writer(const myString& filepath, const Image* image) :ImageWriter(filepath, image) {}
void PBM_Writer::saveImage()
{
	int width = image->getWidth();
	int height = image->getHeight();
	writeStream << "P1" << '\n';
	writeStream << width << " " << height << '\n';

	int imageGridSize = width * height;
	for (int i = 0; i < imageGridSize; i++)
	{
		if (i == width - 1)
			writeStream << '\n';

		if ((*image)[i].getColorValue() == RGB_WHITE)
			writeStream << PBM_WHITE << ' ';
		else
			writeStream << PBM_BLACK << ' ';
	}
}