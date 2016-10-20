#include "battlecruiser.h"
#include "factory.h"
#include <iostream>

using namespace std;

Unit * createBc(){
	return new BattleCruiser;
}

static bool ok = Factory::getInstance()->regist3r(
	"battlecruiser", createBc);



BattleCruiser::~BattleCruiser()
{
	cout << "BattleCruiser destructor" << endl;
}
void BattleCruiser::move(int x, int y) 
{
	cout << "BattleCruiser moved!" << endl;
}
void BattleCruiser::attack(int x, int y)
{
	cout << "BattleCruiser attacked!";
}