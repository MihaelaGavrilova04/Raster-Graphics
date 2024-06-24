#pragma once
#include <stdexcept>
#include "myVector.hpp"
#include "RGB.h"
enum class PictureType
{
	UNKNOWN = -1,
	PPM,
	PGM,
	PBM
};

class Image
{
public:
	Image(const PictureType& type, int width, int height, int maxPixelValue, const myVector<RGB> & pixels);
	Image(const PictureType& type, int width, int height, const myVector<RGB>& pixels);

	const RGB& operator[](int index)const;
	RGB& operator[](int index);
	int getWidth()const;
	int getHeight()const;
	int getMaxValue()const;
	const PictureType& getType()const;
		//debug purposes
	void printVector()const;
	void printPixel(int index)const;
	const myVector<RGB>& getPixels()const;
	myVector<RGB>& getPixels();

	const RGB& getPixel(int x, int y)const;

	void resetPixels(const myVector<RGB>& newPixels);
	const char* getTypeString(const PictureType& type)const;
	
private:
	PictureType type = PictureType::UNKNOWN;
	int width = 0;
	int height = 0;
	int maxPixelValue = 0;
	myVector<RGB>pixels;

	inline int getNumPixels()const;
	void setPictureType(const PictureType& type);
};