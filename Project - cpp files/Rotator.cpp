#include "Rotator.h"


void Rotator::rotate(Image* image,Direction direction)
{
    previousDirection = direction;

    switch (direction)
    {
    case Direction::LEFT:    
        applyRotation(image, Direction::LEFT, rotateLeftOperation);
        break;
    case Direction::RIGHT:
        applyRotation(image, Direction::RIGHT, rotateRightOperation);
        break;
    default:
        throw std::logic_error("Invalid direction");
    }
}

void Rotator::applyRotation(Image* image,Direction direction, rotationFunc operation)
{
    int width = image->getWidth();
    int height = image->getHeight();
    myVector<RGB> rotatedPixels(width * height); 
    rotatedPixels.setSize(width * height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            RGB& pixel = (*image)[y * width + x];
            operation(image, x, y, pixel, rotatedPixels);
        } 
    }

    int rotatedWidth = (direction == Direction::LEFT) ? height : width;
    int rotatedHeight = (direction == Direction::LEFT) ? width : height;

    if (image->getType() == PictureType::PBM)
    {
        Image rotatedImage(image->getType(), rotatedWidth, rotatedHeight, rotatedPixels);
        *image = rotatedImage;
    }
    else
    {
        Image rotatedImage(image->getType(), rotatedWidth, rotatedHeight, image->getMaxValue(), rotatedPixels);
        *image = rotatedImage;
    }
}
    
void Rotator::rotateLeftOperation(Image* image, int x, int y, RGB& pixel, myVector<RGB>& rotatedPixels) {
    int newWidth = image->getHeight(); 
    int newHeight = image->getWidth(); 
    int newX = y;
    int newY = newHeight - 1 - x;
    rotatedPixels[newY * newWidth + newX] = pixel;
}


void Rotator::rotateRightOperation(Image* image, int x, int y, RGB& pixel, myVector<RGB>& rotatedPixels)
{
    int newWidth = image->getHeight(); 
    int newHeight = image->getWidth();
    int newX = newWidth - 1 - y;
    int newY = x;
    rotatedPixels[newY * newWidth + newX] = pixel;
   
}
