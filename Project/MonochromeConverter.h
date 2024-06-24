#pragma once
#include "ImageConverter.h"
#include "RGB.h"
class MonochromeConverter : public ImageConverter
{
public:

    MonochromeConverter() = default;
    void toMonochrome(Image* image);
private:
    void operate(int x, int y, RGB& pixel) override;

};
