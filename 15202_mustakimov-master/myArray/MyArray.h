#pragma once

#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <utility>

template <class T>
class MyArray
{
private:
	size_t size;
	size_t capacity;
	T * data;

	void resizeIfNeeded();
public:
	MyArray(size_t capacity = 10);
	MyArray(size_t count, T item);
	MyArray(const MyArray & myArray); // Copy contructor
	MyArray(MyArray && myArray); // Move contructor
	~MyArray();

	void add(T item);
	void insert(size_t position, T item);

	T & operator [](size_t index);
	const T & operator [](size_t index) const;

	MyArray & operator =(const MyArray & other); // Copy
	MyArray & operator =(MyArray && other); // Move

	T get(size_t index);

	size_t getLength()
	{
		return size;
	}
};

/* If there are no place for one new element, resize data */
template <class T>
void MyArray<T>::resizeIfNeeded()
{
	if (size >= capacity)
	{
		int * newData = (T*)realloc(data, sizeof(T) * capacity * 2);
		if (newData == nullptr)
		{
			throw "Reallocation error";
		}
		else
		{
			data = newData;
			capacity *= 2;
		}
	}
}

template <class T>
MyArray<T>::MyArray(size_t capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->data = (T*)malloc(sizeof(T) * capacity);
}

template <class T>
MyArray<T>::MyArray(size_t count, T item) : MyArray(count)
{
	this->size = count;

	for (size_t i = 0; i < count; i++)
	{
		data[i] = item;
	}
}

// Copy constructor
template <class T>
MyArray<T>::MyArray(const MyArray<T> & myArray)
	: MyArray(myArray.capacity)
{
	this->size = myArray.size;

	memcpy(this->data, myArray.data, size*sizeof(int));
}

// Move constructor
template <class T>
MyArray<T>::MyArray(MyArray<T> && myArray)
{
	std::swap(this->size, myArray.size);
	std::swap(this->capacity, myArray.capacity);
	std::swap(this->data, myArray.data);
}

template <class T>
MyArray<T>::~MyArray()
{
	free(data);
}

template <class T>
void MyArray<T>::add(T item)
{
	resizeIfNeeded();

	data[size] = item;
	size++;
}

template <class T>
void MyArray<T>::insert(size_t position, T item)
{
	if (position >= 0 && position <= size)
	{
		resizeIfNeeded();

		for (size_t i = size; i > position; i--)
		{
			data[i] = data[i - 1];
		}

		data[position] = item;
		size++;
	}
	else
	{
		throw "Position out of range";
	}
}

template <class T>
T & MyArray<T>::operator[](size_t index)
{
	assert(index >= 0 && index < size);
	return data[index];
}

template <class T>
const T & MyArray<T>::operator[](size_t index) const
{
	assert(index >= 0 && index < size);
	return data[index];
}

// Copy
template <class T>
MyArray<T> & MyArray<T>::operator =(const MyArray<T> & other)
{
	free(data);
	data = (T*)malloc(sizeof(T) * other.capacity);

	this->size = other.size;
	this->capacity = other.capacity;

	memcpy(this->data, other.data, size*sizeof(T));

	return *this;
}

// Move
template <class T>
MyArray<T> & MyArray<T>::operator =(MyArray<T> && other)
{
	std::swap(this->size, other.size);
	std::swap(this->capacity, other.capacity);
	std::swap(this->data, other.data);

	return *this;
}

template <class T>
T MyArray<T>::get(size_t index)
{
	if (index >= 0 && index < size)
	{
		return data[index];
	}
	else
	{
		throw "Index out of range";
	}
}

