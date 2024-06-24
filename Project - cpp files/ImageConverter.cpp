#include "ImageConverter.h"
#include "RGB.h"
//ImageConverter::ImageConverter(Image* image): ImageManipulation(image){}
void ImageConverter::colorToGray(RGB& pixel)
{
    int grayValue = (int)(redCoeff * pixel.red + greenCoeff * pixel.green + blueCoeff * pixel.blue);
    pixel.red = pixel.green = pixel.blue = grayValue;
}
/*void ImageConverter::convert(colorConverter operate)
{
    int width = imageToModify->getWidth();
    int height = imageToModify->getHeight();
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int pixelPosition = y * width + x;
            RGB& pixel = (*imageToModify)[pixelPosition];
            operate(x, y, pixel); 
            (*imageToModify)[pixelPosition] = pixel;
        }
    }
}

*/