#include "MonochromeCommand.h"

MonochromeCommand::MonochromeCommand(MonochromeConverter* converter)
    : converter(converter){}

void MonochromeCommand::execute(Image* image)
{
        previousPixels = image->getPixels();
        converter->toMonochrome(image);
}

void MonochromeCommand::undo()
{
    image->resetPixels(previousPixels);
}