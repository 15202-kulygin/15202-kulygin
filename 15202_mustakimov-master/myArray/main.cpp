#include <iostream>
#include "MyArray.h"

using namespace std;

MyArray<int> getArray()
{
    return MyArray<int>(5);
}

int main()
{
    MyArray<int> array;
    array = getArray();
    array.add(42);

    cout << "Hello from main.cpp!" << endl << array[0] << endl;
    return 0;
}
