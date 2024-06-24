#include "GrayscaleConverter.h"
void GrayscaleConverter::operate(int y, int x, RGB& pixel)
{
	colorToGray(pixel);
}
void GrayscaleConverter::toGrayscale(Image* image)
{
	if (!image)
		throw std::invalid_argument("Image is nullptr!\n");
    myVector<RGB>& pixels = image->getPixels();
    for (int y = 0; y < image->getHeight(); ++y) {
        for (int x = 0; x < image->getWidth(); ++x) {
            operate(y, x, pixels[y * image->getWidth() + x]);
        }
    }
}
