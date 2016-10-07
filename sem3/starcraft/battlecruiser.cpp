#include "battlecruiser.h"

#include <iostream>

using namespace std;

BattleCruiser::~BattleCruiser()
{
	cout << "BattleCruiser destructor" << endl;
}
void BattleCruiser::move(int x, int y) 
{
	cout << "Battlecruiser moved!" << endl;
}
void BattleCruiser::attack(int x, int y)
{
	cout << "BattleCruiser attacked!";
}