#include "PGM_Reader.h"
PGM_Reader::PGM_Reader(const char* filepath) :ImageReader(filepath){}
PGM_Reader::PGM_Reader(const myString& filepath):PGM_Reader(filepath.c_str()){}
Image* PGM_Reader::createImage()const
{
    int vectorSize = allData.getSize();
    int width = 0, height = 0, maxColorValue = 0;
    myVector<RGB> pixels;
    char format[10];
    bool dimensionsFound = false;
    bool maxColorValueFound = false;
    bool read = 0;
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

        int color;
        while (ss >> color) {
            pixels.pushBack(RGB(color, color, color));
        }

    }

    if (!dimensionsFound || !maxColorValueFound) {
        throw std::runtime_error("format error! \n");
    }

    return new Image(PictureType::PGM, width, height, maxColorValue, pixels);
}