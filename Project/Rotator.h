#pragma once
#include "myVector.hpp"
#include "RGB.h"
#include "Image.h"
typedef void (*rotationFunc)(Image* image, int x, int y, RGB& pixel, myVector<RGB>& rotatedPixels);

enum class Direction
{
    LEFT,
    RIGHT
};

class Rotator 
{
public:
    void rotate(Image* image,Direction direction);
private:
    void applyRotation(Image* image, Direction direction, rotationFunc operation);
    static void rotateLeftOperation(Image* image,int x, int y, RGB& pixel, myVector<RGB>& rotatedPixels);
    static void rotateRightOperation(Image* image, int x, int y, RGB& pixel, myVector<RGB>& rotatedPixels);

    Direction previousDirection;
};
