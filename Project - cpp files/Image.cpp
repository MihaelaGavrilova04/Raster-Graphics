#include "Image.h"

Image::Image(const PictureType& type, int width, int height,int maxPixelValue, const myVector<RGB>& initPixels):type(type)
{
	if (width < 0 || height < 0 || initPixels.empty())
	throw std::invalid_argument("Invalid arguments passed to construct image! \n");

	this->width = width;
	this->height = height;
	this->maxPixelValue = maxPixelValue;
	pixels.setSize(width * height); /////////////////////////
	pixels=initPixels; //copy constr of vector
}
Image::Image(const PictureType& type, int width, int height, const myVector<RGB>& initPixels):type(type)
{
	if (width < 0 || height < 0 || initPixels.empty())
		throw std::invalid_argument("Invalid arguments passed to construct image! \n");

	this->width = width;
	this->height = height;
	pixels = initPixels;
}

const RGB& Image::operator [] (int index)const
{
	if (index >= getNumPixels())
		throw std::invalid_argument("No such index!\n");
	return pixels[index];
}
RGB& Image::operator [] (int index)
{
	if (index >= getNumPixels())
		throw std::invalid_argument("No such index! \n");
	return pixels[index];
}
int Image::getNumPixels()const
{
	return width * height;
}
void Image::setPictureType(const PictureType& type)
{
	if (type == PictureType::UNKNOWN)
		throw std::invalid_argument("Cant process unknown image!\n");
	this->type = type;
}
int Image::getWidth()const
{
	return width;
}
int Image::getHeight()const
{
	return height;
}
int Image::getMaxValue()const
{
	return maxPixelValue;
}
const PictureType& Image::getType()const
{
	return type;
}
const char* Image::getTypeString(const PictureType& type)const
{
	switch (type) {
	case PictureType::PPM:
		return "PPM";
	case PictureType::PGM:
		return "PGM";
	case PictureType::PBM:
		return "PBM";
	case PictureType::UNKNOWN:
	default:
		return "UNKNOWN";
	}
}

void Image::printPixel(int index)const
{
	std::cout << pixels[index].red << " " << pixels[index].green << " " << pixels[index].blue << '\n';
}


void Image::printVector()const
{
	int size = pixels.getSize();
	for (int i = 0; i < size; i++)
	{
		if (i == width)
		std::cout << pixels[i].red << " " << pixels[i].green << " " << pixels[i].blue<<'\n';
	}
}

const myVector<RGB>& Image::getPixels()const
{
	return pixels;
}

myVector<RGB>& Image::getPixels()
{
	return pixels;
}

const RGB& Image::getPixel(int x, int y)const
{
	return pixels[y*height + x];
}

void Image::resetPixels(const myVector<RGB>& newPixels)
{
	int numPixels = getNumPixels();
	int sizeTest = newPixels.getSize();
	
	if (newPixels.getSize() != numPixels)
	throw std::invalid_argument("Incompatible!");

	for (int i = 0; i < numPixels; i++)
	{
		pixels[i] = newPixels[i];
	}
}








