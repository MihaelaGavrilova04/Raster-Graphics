#pragma once

#include "Image.h"
#include "SharedPtr.hpp"
#include <iostream>

class Collage {
public:
    Collage() = default;

    static SharedPtr<Image> horizontalCollage(const SharedPtr<Image>& image1, const SharedPtr<Image>& image2);
    static SharedPtr<Image> verticalCollage(const SharedPtr<Image>& image1, const SharedPtr<Image>& image2);

private:
    // helper
    static bool areCompatible(const SharedPtr<Image>& image1, const SharedPtr<Image>& image2);
};
