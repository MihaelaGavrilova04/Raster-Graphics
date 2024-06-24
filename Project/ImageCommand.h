#pragma once
#include "Image.h"
class ImageCommand {
public:
    virtual ~ImageCommand() {}
    virtual void execute(Image* image) = 0;
    virtual void undo() = 0;   
};
