#include "ImageReader.h"

ImageReader::ImageReader(const char* filepath)
{
	if (!filepath)
		throw std::invalid_argument("Invalid filepath! \n");

	readStream.open(filepath);
	if (!readStream.is_open())
		throw std::logic_error("Error while opening file SAD! \n");
	getAllFileInfo();
}
ImageReader::ImageReader(const myString& filepath):ImageReader(filepath.c_str()){}

void ImageReader::getAllFileInfo() {
    if (!readStream.is_open()) {
        throw std::runtime_error("File not opened");
    }

    char buffer[MAX_BUFFER_SIZE] = { '\0' };
    while (readStream.getline(buffer, MAX_BUFFER_SIZE)) {
        if (strlen(buffer) > 0) {
            myString toAdd(buffer);
            allData.pushBack(toAdd);
        }
    }
}
Image* ImageReader::getImage()const
{
	return createImage();
}

ImageReader::~ImageReader()
{
	if (readStream.is_open())
	{
		readStream.close();
	} 
}
void ImageReader::printVector()const
{
   int size = allData.getSize();
  for (int i = 0; i < size; i++)
  {
    std::cout << allData[i].c_str()<<'\n';
  }
}
