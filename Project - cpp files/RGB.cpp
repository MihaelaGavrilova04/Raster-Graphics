#include "RGB.h"

RGB::RGB(int redValue, int greenValue, int blueValue)
{
	setRed(redValue);
	setGreen(greenValue);
	setBlue(blueValue);
}

void RGB::setRed(int value)
{
	if(value > MAX_VALUE)
		throw std::invalid_argument("Invalid colour value");
	red = value;
}
void RGB::setGreen(int value)
{
	if (value > MAX_VALUE)
		throw std::invalid_argument("Invalid colour value");
	green = value;
}
void RGB::setBlue(int value)
{
	if (value > MAX_VALUE)
		throw std::invalid_argument("Invalid colour value");
	blue = value;
}
std::ostream& operator <<(std::ostream& os, const RGB& color)
{
	return os << color.red << ' ' << color.green << ' ' << color.blue;
}

int RGB::getColorValue()const
{
	return red;
}
