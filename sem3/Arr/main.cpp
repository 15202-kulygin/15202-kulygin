#include <iostream>
#include "arr.h"

using namespace std;

int main (void)
{
	Arr a(5, 8); // constructor is working
	a.add(0);
	a.add(1);
	a.add(2);
	a.add(3);
	a.add(4);
	a.insert(17);
	a.add(25);
	a.insert(777);

	a.printArr();
	a.setArr(1337, 2);
	a.printArr();
	Arr b(10, 666);
	b.printArr();
	b = a;
	b.printArr();
	Arr c = a;
	cout << "Printing c" << endl;
	c.printArr();

	/*
	int test = -1;
	test = a.get(0);
	printf("test %d\n", test);
	test = a.get(1);
	printf("test %d\n", test);
	test = a.get(2);
	printf("test %d\n", test);
	test = a.get(3);
	printf("test %d\n", test);
	test = a.get(4);
	printf("test %d\n", test);
	
	test = a.get(2);
	printf("test %d\n", test);*/


	char q = ' ';
	cin >> q;
	return 0;
} // destructor is working

