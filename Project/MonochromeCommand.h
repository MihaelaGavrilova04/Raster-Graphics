#pragma once
#include "ImageCommand.h"
#include "MonochromeConverter.h"
#include "SharedPtr.hpp"
class MonochromeCommand:public ImageCommand
{
public:
    MonochromeCommand(MonochromeConverter* converter);

    void execute(Image* image) override;
    void undo() override;
private:
    MonochromeConverter* converter;
    SharedPtr<Image> image;
    myVector<RGB> previousPixels;
};  
