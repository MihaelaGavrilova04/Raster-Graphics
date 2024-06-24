#pragma once
#include <iostream>

template<typename T>
class myVector {
private:
	T* data = nullptr;
	int size = 0;
	int capacity = 0;

	static const int INITIAL_CAPACITY = 20;
	void resize(int newCapacity);
	void indexValidation(int index) const;

	void moveFrom(myVector<T>&& other);
	void copyFrom(const myVector<T>& other);
	void free();
public:
	myVector();
	myVector(int capacity);
	myVector(const myVector<T>& other);
	myVector(myVector<T>&& other);
	myVector<T>& operator=(const myVector<T>& other);
	myVector<T>& operator=(myVector<T>&& other);
	~myVector();

	int getSize() const;
	int getCapacity() const;

	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(const T& element, int index);
	void pushAt(T&& element, int index);
	T popBack();
	T removeAtIndex(int index);

	bool empty() const;
	void setSize(int size);
	T& operator[](int index);
	const T& operator[](int index) const;

	void print()const;
};

template<typename T>
void myVector<T>::print()const
{
	for (int i = 0; i < size; i++)
	{
		std::cout << data[i]<<"  ,  ";
	}
}

template<typename T>
myVector<T>::myVector():capacity(INITIAL_CAPACITY),size(0)
{ 
	data = new T[capacity];
} 


template<typename T>
myVector<T>::myVector(int capacity) : capacity(capacity) 
{
	data = new T[capacity];
}

template<typename T>
myVector<T>::myVector(const myVector<T>& other) 
{
	copyFrom(other);
}
template<typename T>
myVector<T>::myVector(myVector<T>&& other) {
	moveFrom(std::move(other));
}

template<typename T>
myVector<T>& myVector<T>::operator=(const myVector<T>& other) 
{
	if (this != &other) 
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
myVector<T>& myVector<T>::operator=(myVector<T>&& other) 
{
	if (this != &other) 
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
myVector<T>::~myVector()
{
	free();
}

template<typename T>
void myVector<T>::indexValidation(int index) const
{
	if (index >= size) {
		throw std::exception("Out of range");
	}
}
template<typename T>
void myVector<T>::resize(int newCapacity) 
{
	capacity = newCapacity;
	T* temp = new T[capacity];

	if (size > newCapacity) {
		size = newCapacity;
	}

	for (int i = 0; i < size; i++) {
		temp[i] = std::move(data[i]);
	}

	delete[] data;
	data = temp;
}

template<typename T>
int myVector<T>::getSize() const 
{
	return size;
}

template<typename T>
int myVector<T>::getCapacity() const
{
	return capacity;
}

static int getClosestPowOfTwo(int num) 
{
	num--;
	num |= num >> 1;
	num |= num >> 2;
	num |= num >> 4;
	num |= num >> 8;
	num |= num >> 16;
	return ++num;
}

template<typename T>
void myVector<T>::pushBack(const T& element) 
{
	if (size == capacity)
		resize(getClosestPowOfTwo(capacity));

	data[size++] = element;
}

template<typename T>
void myVector<T>::pushBack(T&& element)
{
	if (size == capacity)
	resize(getClosestPowOfTwo(capacity));

	data[size++] = std::move(element);
}

template<typename T>
void myVector<T>::pushAt(const T& element, int index)
{
	indexValidation(index);
	if (size == capacity)
	resize(getClosestPowOfTwo(capacity));

	for (size_t i = size; i > index; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[index] = element;
	size++;
}

template<typename T>
void myVector<T>::pushAt(T&& element, int index) 
{
	indexValidation(index);
	if (size == capacity)
	resize(getClosestPowOfTwo(capacity));

	for (size_t i = size; i > index; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[index] = std::move(element);
	size++;
}

template<typename T>
T myVector<T>::popBack() 
{
	if (empty()) 
	{
		throw std::exception("Nothing to pop back! \n");
	}
	size--;
	return data[size];
}

template<typename T>
T myVector<T>::removeAtIndex(int index) 
{
	indexValidation(index);

	T temp = data[index];
	size--;
	for (int i = index; i < size; i++) {
		data[i] = std::move(data[i + 1]);
	}

	return temp;
}

template<typename T>
bool myVector<T>::empty() const 
{
	return size == 0;
}

template<typename T>
void myVector<T>::setSize(int size)
{
	if (size >= 0)
		this->size = size;
}
template<typename T>
T& myVector<T>::operator[](int index) 
{
	indexValidation(index);

	return data[index];
}

template<typename T>
const T& myVector<T>::operator[](int index) const 
{
	indexValidation(index);

	return data[index];
}

template<typename T>
void myVector<T>::moveFrom(myVector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
	other.size = other.capacity = 0;
}

template<typename T>
void myVector<T>::copyFrom(const myVector<T>& other) 
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];

	for (size_t i = 0; i < other.size; i++) 
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void myVector<T>::free() 
{
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}