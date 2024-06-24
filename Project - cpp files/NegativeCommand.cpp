#include "NegativeCommand.h"

NegativeCommand::NegativeCommand(NegativeConverter* converter) :converter(converter){}

void NegativeCommand::execute(Image* image)
{
		previousPixels = image->getPixels();
		converter->toNegative(image);
}
void NegativeCommand::undo()
{
	image->resetPixels(previousPixels);
}
	