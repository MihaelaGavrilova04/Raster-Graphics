#include "NegativeConverter.h"
void NegativeConverter::operate(int y, int x, RGB& pixel)
{
	pixel.red = 255 - pixel.red;
	pixel.green = 255 - pixel.green;
	pixel.blue = 255 - pixel.blue;
}
void NegativeConverter::toNegative(Image * image)
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
