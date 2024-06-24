#pragma once
#include <iostream>
#pragma once
#include <iostream>

class myString
{
public:
	myString();
	myString(const char* data);
	myString(char* data);

	myString(const myString& other);
	myString(myString&& other) noexcept;
	explicit myString(size_t stringLength);

	myString& operator=(const myString& other);

	myString& operator=(myString&& other) noexcept;
	~myString();

	size_t getCapacity() const;
	size_t getSize() const;

	const char* c_str() const;
	char* data(); 
	myString substr(size_t begin, size_t howMany) const;

	myString& operator+=(const myString& other);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const myString& obj);
	friend std::istream& operator>>(std::istream& is, myString& ref);
	friend myString operator+(const myString& lhs, const myString& rhs);
private:
	void resize(unsigned newAllocatedDataSize);

	void free();
	void copyFrom(const myString& other);

	void moveFrom(myString&& other);

	char* myData;
	size_t _size;
	size_t _allocatedDataSize;
};



bool operator==(const myString& lhs, const myString& rhs);
bool operator!=(const myString& lhs, const myString& rhs);
bool operator<(const myString& lhs, const myString& rhs);
bool operator<=(const myString& lhs, const myString& rhs);
bool operator>(const myString& lhs, const myString& rhs);
bool operator>=(const myString& lhs, const myString& rhs);
