#pragma once
#include "ImageCommand.h"
#include "NegativeConverter.h"
class NegativeCommand:public ImageCommand
{
public:
	NegativeCommand(NegativeConverter* converter);
	void execute(Image* image) override;
	void undo()override;
private:
	NegativeConverter* converter;
	Image* image;
	myVector<RGB> previousPixels;
};
