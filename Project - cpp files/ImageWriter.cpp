#include "ImageWriter.h"
ImageWriter::ImageWriter(const char* filepath, const Image* image):image(image)
{
	if (!filepath)
		throw std::invalid_argument("Invalid filepath! \n");

	writeStream.open(filepath);
	if (!writeStream.is_open())
		throw std::logic_error("Error while opening file! \n");
}
ImageWriter::ImageWriter(const myString& filepath, const Image* image):ImageWriter(filepath.c_str(),image){}

ImageWriter::~ImageWriter()
{
	if (writeStream.is_open())
	{
		writeStream.close();
	}
}
