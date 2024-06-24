#pragma once
#include <iostream>

template <typename T>
class UniquePtr
{
	T* ptr;
public:
	UniquePtr();

	UniquePtr(T* ptr);

	UniquePtr(const UniquePtr&) = delete;

	UniquePtr& operator=(const UniquePtr&) = delete;

	UniquePtr(UniquePtr&&) noexcept;

	UniquePtr& operator=(UniquePtr&&) noexcept;

	T& operator*();

	const T& operator*() const;

	T* operator->();

	const T* operator->() const;

	T* get() const;

	~UniquePtr();
};

template <typename T>
UniquePtr<T>::UniquePtr() : ptr(nullptr) {}
template <typename T>
UniquePtr<T>::UniquePtr(T* ptr) : ptr(ptr)
{}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept
{
	ptr = other.ptr;
	other.ptr = nullptr;
}
template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept
{
	if (this != &other)
	{
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}
	return *this;
}

template <typename T>
T& UniquePtr<T>::operator*()
{
	return *ptr;
}

template <typename T>
const T& UniquePtr<T>::operator*() const
{
	return *ptr;
}

template <typename T>
T* UniquePtr<T>::operator->()
{
	return ptr;
}

template <typename T>
const T* UniquePtr<T>::operator->() const
{
	return ptr;
}

template <typename T>
T* UniquePtr<T>::get() const
{
	return ptr;
}
template <typename T>
UniquePtr<T>::~UniquePtr()
{
	delete ptr;
}