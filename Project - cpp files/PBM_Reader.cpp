#include "PBM_Reader.h"

PBM_Reader::PBM_Reader(const char* filename) :ImageReader(filename) {}
PBM_Reader::PBM_Reader(const myString& filename):ImageReader(filename.c_str()){}
Image* PBM_Reader::createImage()const
{
        int vectorSize = allData.getSize();
        int width = 0;
        int height = 0;
        myVector<RGB> pixels;
        char format[10];
        bool dimensionsFound = false;
        bool read = 0;
        for (int i = 0; i < vectorSize; i++) 
        {
            if (allData[i][0] == '#') // Skip comments
                continue;

            std::stringstream ss(allData[i].c_str());
            if (read == 0)
            {
                ss >> format;
                read = 1;
            }

            if (!dimensionsFound)//read width & height
            {
                if (ss >> width >> height) 
                {
                    dimensionsFound = true;
                    continue;
                }
            }

            int currentColor;
            while (ss >> currentColor) 
            {
                if (currentColor == WHITE) 
                {
                    pixels.pushBack(RGB(WHITE, WHITE, WHITE));
                }
                else if (currentColor == BLACK) 
                {
                    pixels.pushBack(RGB(BLACK, BLACK, BLACK));
                }
                else 
                {
                    throw std::logic_error("Invalid file!\n");
                }
            }
        }

        if (!dimensionsFound) 
        {
            throw std::runtime_error("Unable to read dimensions.\n");
        }

        return new Image(PictureType::PBM, width, height, pixels);
    }
