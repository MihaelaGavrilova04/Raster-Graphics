#include "Collage.h"

SharedPtr<Image> Collage::horizontalCollage(const SharedPtr<Image>& image1, const SharedPtr<Image>& image2)
{
    if (!areCompatible(image1, image2))
        throw std::logic_error("Incompatible");

    int width = image1->getWidth() + image2->getWidth();
    int height = image1->getHeight();
    PictureType type = image1->getType();

    myVector<RGB> collagePixels(width * height);

    int firstImageWidth  = image1->getWidth();
    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < firstImageWidth; x++) 
        {
            collagePixels.pushBack(image1->getPixel(x, y));
        }
    }

    int secondImageWidth = image1->getWidth();
    for (int y = 0; y < height;y++) {
        for (int x = 0; x < secondImageWidth;x++) {
            collagePixels.pushBack(image2->getPixel(x, y));
        }
    }

    Image* collage = new Image(type, width, height, collagePixels);

    return SharedPtr<Image>(collage);
}

SharedPtr<Image> Collage::verticalCollage(const SharedPtr<Image>& image1, const SharedPtr<Image>& image2) 
{
    if (!areCompatible(image1, image2))
        throw std::logic_error("Incompatible");

    int width = image1->getWidth();
    int height = image1->getHeight() + image2->getHeight();
    PictureType type = image1->getType();

    myVector<RGB> collagePixels(width * height);

    int firstImageHeight = image1->getHeight();
    for (int y = 0; y < firstImageHeight; y++)
    {
        for (int x = 0; x < width; x++) {
            collagePixels.pushBack(image1->getPixel(x, y));
        }
    }

    int secondImageHeight = image2->getHeight();
    for (int y = 0; y < secondImageHeight; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            collagePixels.pushBack(image2->getPixel(x, y));
        }
    }

    Image* collage = new Image(type, width, height, collagePixels);

    return SharedPtr<Image>(collage);
}

bool Collage::areCompatible(const SharedPtr<Image>& image1, const SharedPtr<Image>& image2)
{
    if (!image1.isInitlized() || !image2.isInitlized())
        return false;

    if (image1->getType() != image2->getType() ||
        image1->getWidth() != image2->getWidth() ||
        image1->getHeight() != image2->getHeight()) {
        return false;
    }

    return true;
}
