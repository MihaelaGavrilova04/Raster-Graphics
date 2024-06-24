#pragma once
#include "myString.h"
class imageFormat
{
	myString name;
	myString extension;

public:
	imageFormat(const myString& fileName);
	const myString& getName() const;
	const myString& getExtension() const;
};