#pragma once

#include <iostream>

template <typename T, const int S>
class myStack
{
private:
	T arr[S];
	size_t size = 0;
public:

	void push(const T& obj);
	void push(T&& obj);

	const T& peek() const;
	void pop();

	bool isEmpty() const;
	bool isFull() const;
};


template <typename T, const int S>
void myStack<T, S>::push(const T& obj)
{
	if (size >= S)
		return;
	arr[size++] = obj;
}

template <typename T, const int S>
void myStack<T, S>::push(T&& obj)
{
	if (size >= S)
		return;
	arr[size++] = std::move(obj);
}

template <typename T, const int S>
const T& myStack<T, S>::peek() const
{
	if (isEmpty())
		throw std::out_of_range("Error!");

	return arr[size - 1];
}

template <typename T, const int S>
void myStack<T, S>::pop()
{
	if (isEmpty())
		throw std::out_of_range("Error!");
	size--;
}

template <typename T, const int S>
bool myStack<T, S>::isEmpty() const
{
	return size == 0;
}

template <typename T, const int S>
bool myStack<T, S>::isFull() const
{
	return size == S;
}