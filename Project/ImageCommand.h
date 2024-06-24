#pragma once
#include "Image.h"
#include "SharedPtr.hpp"
class ImageCommand {
public:
    virtual ~ImageCommand() {}
    virtual void execute(Image* image) = 0;
    virtual void undo() = 0;   
};