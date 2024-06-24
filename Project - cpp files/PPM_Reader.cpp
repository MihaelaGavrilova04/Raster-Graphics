#include "PPM_Reader.h"
//0 represents black and 255 represents white.
PPM_Reader::PPM_Reader(const char* filepath):ImageReader(filepath){}
PPM_Reader::PPM_Reader(const myString& filepath):ImageReader(filepath.c_str()){}
Image* PPM_Reader:: createImage()const 
{
    int vectorSize = allData.getSize();
    char format[3];
    bool read = 0;
    int width = 0, height = 0, maxColorValue = 0;
    myVector<RGB> pixels;

    bool dimensionsFound = false;
    bool maxColorValueFound = false;

    for (int i = 0; i < vectorSize; i++) {
        if (allData[i][0] == '#') //skip comments
            continue;

        std::stringstream ss(allData[i].c_str());
        if (read == 0)
        {
            ss >> format;
            read = 1;
        }
        if (!dimensionsFound) {
            if (ss >> width >> height) {
                dimensionsFound = true;
                continue;
            }
        }

        if (!maxColorValueFound) {
            if (ss >> maxColorValue) {
                maxColorValueFound = true;
                if (maxColorValue > DEFAULT_MAX_VALUE)
                 maxColorValue = DEFAULT_MAX_VALUE;
                continue;
            }
        }

        int red = 0;
        int green = 0;
        int blue = 0;
        while (ss >> red>> green>> blue) {
            pixels.pushBack(RGB(red, green, blue));
        }
    }

    if (!dimensionsFound || !maxColorValueFound) {
        throw std::runtime_error("PPM format error! \n");
    }

    return new Image(PictureType::PPM, width, height, maxColorValue, pixels);
}