#include "zergling.h"
#include "factory.h"
#include <iostream>

using namespace std;

namespace 
{
	Unit * createZerg(){
		return new Zergling;
	}
	bool ok = Factory::getInstance()->regist3r(  // можно static bool, но без namespace
		"zergling", createZerg);
}



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
	cout << "ZergLing attacked!" << endl;
}