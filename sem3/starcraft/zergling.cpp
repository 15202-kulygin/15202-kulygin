#include "zergling.h"

#include <iostream>

using namespace std;


Zergling::~Zergling()
{
	cout << "Zergling destructor" << endl;
}
void Zergling::move(int x, int y) 
{
	cout << "ZergLing moved!" << endl;
}
void Zergling::attack(int x, int y)
{
	cout << "ZergLing attacked!";
}