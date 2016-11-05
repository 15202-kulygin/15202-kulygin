#include "battlecruiser.h"
#include "factory.h"
#include <iostream>

using namespace std;

auto createBc2 = []() -> Unit * {return new BattleCruiser;}; // лямбда-функции --- прочитать

Unit * createBc(){
	//return new BattleCruiser;
	return createBc2();
}

static bool ok = Factory<Unit, std::string, Unit*(*)()>::getInstance()->regist3r(
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