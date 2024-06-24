#include "MonochromeConverter.h"

void MonochromeConverter::operate(int y, int x, RGB& pixel) 
{
    colorToGray(pixel);
    int monoValue = pixel.red > 127 ? 255 : 0;
    pixel.red = pixel.green = pixel.blue = monoValue;
}

void MonochromeConverter::toMonochrome(Image* image)
{
    if (!image)
        return;
    myVector<RGB>& pixels = image->getPixels();
    for (int y = 0; y < image->getHeight(); y++)
    {
        for (int x = 0; x < image->getWidth(); x++)
        {
            operate(y, x, pixels[y * image->getWidth() + x]);
        }
    }
}
