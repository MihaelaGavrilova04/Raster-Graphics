#pragma once

#include "Image.h"
#include <stdexcept>
#include "myVector.hpp"

class Collage {
public:
    Collage() = default;

    static Image* horizontalCollage(Image* image1, Image* image2);
    static Image* verticalCollage(Image* image1, Image* image2);

private:
    // helper
    static bool areCompatible(Image* image1, Image* image2);
};
