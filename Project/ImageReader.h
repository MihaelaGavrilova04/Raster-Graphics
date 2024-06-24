#pragma once
#include <iostream>
#include "myVector.hpp"
#include "myString.h"
#include "Image.h"
class ImageReader
{
protected:
	std::ifstream readStream;
	myVector<myString> allData; //we will collect all the info from the file
	virtual Image* createImage()const = 0;
	static const unsigned int DEFAULT_MAX_VALUE = 255;
public:
	ImageReader() = default;
	ImageReader(const char* filepath);
	ImageReader(const myString& filepath);
	virtual ~ImageReader();
	virtual Image* getImage()const;

	//debug purpose
    void printVector()const;
private:
	void getAllFileInfo(); //this function inits the vector, containing allData
	static constexpr int magicNumLength = 2;
	static constexpr int MAX_BUFFER_SIZE = 1024;
};