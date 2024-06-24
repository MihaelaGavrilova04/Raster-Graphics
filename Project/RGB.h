#pragma once
#include <stdexcept>
#include <fstream>
class RGB
{
public:
	RGB() = default;
	RGB(int redValue, int greenValue, int blueValue);
	int getColorValue()const;

	int red = 0;
	int green = 0;
	int blue = 0;
private:
	void setRed(int value);
	void setGreen(int value);
	void setBlue(int value);

	friend std::ostream& operator <<(std::ostream& os, const RGB& color);
	static constexpr int MAX_VALUE = 255;
};