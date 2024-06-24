#include "imageFormat.h"
#include <sstream>

imageFormat::imageFormat(const myString& fileName)
{
	const char* beg = fileName.c_str();
	const char* end = fileName.c_str() + fileName.getSize();
	const char* iter = end;

	while (iter != beg && *iter != '.') 
	{
		iter--;
	}

	this->name = fileName.substr(0, iter - beg);
	this->extension = fileName.substr(iter - beg, end - iter);
}

const myString& imageFormat::getName() const
{
	return name;
}

const myString& imageFormat::getExtension() const
{
	return extension;
}