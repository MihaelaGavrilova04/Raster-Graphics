#include "myString.h"
#pragma warning (disable : 4996)
#include "MyString.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable : 4996)


static unsigned roundToPowerOfTwo(unsigned v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
	return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

myString::myString() : myString("") {}

myString::myString(const char* data)
{
	_size = std::strlen(data);
	_allocatedDataSize = dataToAllocByStringLen(_size);
	myData = new char[_allocatedDataSize];
	std::strcpy(myData, data);
}
myString::myString(char* data)
{
	_size = std::strlen(data);
	_allocatedDataSize = dataToAllocByStringLen(_size);
	myData = new char[_allocatedDataSize];
	std::strcpy(myData, data);
}

myString::myString(size_t stringLength)
{
	_allocatedDataSize = dataToAllocByStringLen(stringLength);
	myData = new char[_allocatedDataSize];
	_size = 0;
	myData[0] = '\0';
}

myString::myString(const myString& other)
{
	copyFrom(other);
}
myString::myString(myString&& other) noexcept
{
	moveFrom(std::move(other));
}


void myString::moveFrom(myString&& other)
{
	myData = other.myData;
	other.myData = nullptr;

	_size = other._size;
	other._size = 0;

	_allocatedDataSize = other._allocatedDataSize;
	other._allocatedDataSize = 0;
}


myString& myString::operator=(const myString& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

myString& myString::operator=(myString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}


myString::~myString()
{
	free();
}

size_t myString::getCapacity() const
{
	return _allocatedDataSize - 1;
}

size_t myString::getSize() const
{
	return _size;
}

const char* myString::c_str() const
{
	return myData;
}

myString& myString::operator+=(const myString& other)
{
	if (getSize() + other.getSize() + 1 > _allocatedDataSize)
		resize(dataToAllocByStringLen(getSize() + other.getSize()));

	// we need to use strncat instead of strcat, because strcat will not work for str += str 
	// (the terminating zero of str will be destroyed by the first char)
	std::strncat(myData, other.myData, other.getSize());

	_size = getSize() + other.getSize();
	return *this;
}

char& myString::operator[](size_t index)
{
	return myData[index]; // no security check!!
}

const char& myString::operator[](size_t index) const
{
	return myData[index]; // no security check!!
}

std::ostream& operator<<(std::ostream& os, const myString& obj)
{
	return os << obj.myData;
}

std::istream& operator>>(std::istream& is, myString& ref)
{
	char buff[1024];
	is >> buff;
	size_t buffStringSize = std::strlen(buff);

	if (buffStringSize > ref.getCapacity())
		ref.resize(dataToAllocByStringLen(buffStringSize));

	strcpy(ref.myData, buff);
	ref._size = buffStringSize;
	return is;
}

void myString::resize(unsigned newAllocatedDataSize)
{
	char* newData = new char[newAllocatedDataSize + 1];
	std::strcpy(newData, myData);
	delete[] myData;
	myData = newData;
	_allocatedDataSize = newAllocatedDataSize;
}

void myString::free()
{
	delete[] myData;
}

void myString::copyFrom(const myString& other)
{
	_allocatedDataSize = other._allocatedDataSize;
	myData = new char[_allocatedDataSize];
	std::strcpy(myData, other.myData);
	_size = other._size;
}

myString operator+(const myString& lhs, const myString& rhs)
{
	myString result(lhs.getSize() + rhs.getSize());
	result += lhs; // no resize is needed
	result += rhs;
	return result;
}

bool operator==(const myString& lhs, const myString& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const myString& lhs, const myString& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const myString& lhs, const myString& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const myString& lhs, const myString& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const myString& lhs, const myString& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const myString& lhs, const myString& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
myString myString::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > getSize())
		throw std::length_error("Error, Substr out of range");


	myString res(howMany + 1);
	strncat(res.myData, myData + begin, howMany);
	return res;
}
char* myString::data() {
	return myData;
}
