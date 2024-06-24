#pragma once
#include "ImageCommand.h"
#include "GrayscaleConverter.h"
class GrayscaleCommand:public ImageCommand
{
public:
    GrayscaleCommand(GrayscaleConverter* converter);

    void execute(Image* image) override;
    void undo() override;

private:
    GrayscaleConverter* converter;
    Image* toUndo = nullptr;
    myVector<RGB> previousPixels;
};
