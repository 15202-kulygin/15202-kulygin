#include "Arr.h"
#include <iostream>

using namespace std;

Arr::Arr()
{
	capacity = 10;
	cout << "constructor" << endl;
	cout << "Default capacity stated == 10" << endl;
	arr = new int [capacity];
	size = 0;
}
Arr::Arr(int _capacity, int value) 
{ // constructor
	cout << "constructor" << endl;
	capacity = _capacity;
	size = 0;
	arr = new int [capacity];
	for (int i = 0; i < capacity; ++i)
	{
		arr[i] = value;
	}
}
Arr::~Arr() //destructor
{
	cout << "destructor" << endl;
	delete [] arr;
	arr = 0;
}
void Arr::add (int elem)
{
	
	if (size + 1 >= capacity) 
	{
		int * temp = new int [size];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = arr[i];
		}
		capacity *= 2;
		delete [] arr;
		arr = new int [capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = temp[i];
		}
		size++;
		arr[size - 1] = elem;
		for (int i = size; i < capacity; ++i)
		{
			arr[i] = 0;
		}
		delete [] temp;
	}		
	else
	{
		size++;
		arr[size - 1] = elem;
	}
}
void Arr::printArr()
{
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}
void Arr::setArr(int value, int ind)
{
	if ((ind < 0) || (ind >= size))
	{
		cout << "The index is wrong" << endl;
		return;
	}
	else
	{
		arr[ind] = value;
		return;
	}
}
void Arr::insert (int elem)
{
	
	if (size + 1 >= capacity) 
	{
		int * temp = new int [size];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = arr[i];
		}
		capacity *= 2;
		delete [] arr;
		arr = new int [capacity];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = temp[i];
		}
		delete [] temp;
	}	
	size++;	
	int toadd = (size - 1) / 2;
	int temp = arr[toadd];
	arr[toadd] = elem;
	for (int i = toadd + 1; i < size; ++i)
	{
		int temp1 = arr[i];
		arr[i] = temp;
		temp = temp1;
	}
}
int Arr::get (int ind)
{
	if ((ind >= size) || (ind < 0))
	{
		cout << "The index is wrong" << endl;
		return -1;
	}
	else
	{
		return arr[ind];
	}
}
int Arr::operator [] (int ind)
{
	if ((ind < 0) || (ind >= size))
	{
		cout << "The index in operator [] is wrong" << endl;
		return -1;
	}
	else
	{
		return arr[ind];
	}
}
Arr& Arr::operator = (Arr &curArr) 
{
    delete [] arr;
    size = curArr.size;
    capacity = curArr.capacity;
    arr = new int [capacity];
    for (int i = 0; i < size; i++)
    {
        arr[i] = curArr.arr[i];
    }
    return *this;
}

