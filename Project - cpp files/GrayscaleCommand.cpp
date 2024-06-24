#pragma once
#include "GrayscaleCommand.h"
GrayscaleCommand::GrayscaleCommand(GrayscaleConverter* converter) :converter(converter){}

void GrayscaleCommand::execute(Image* image)
{
	if (!image)
		throw std::invalid_argument("Image is nullptr!\n");
	toUndo = image;
    previousPixels = image->getPixels();
	converter->toGrayscale(image);
}
void GrayscaleCommand::undo()
{
	toUndo->resetPixels(previousPixels);
}