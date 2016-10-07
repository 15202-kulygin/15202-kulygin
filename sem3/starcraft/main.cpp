#include "unit.h"
#include "battlecruiser.h"
#include "zergling.h"
#include <iostream>

using namespace std;

int main ()
{
	Unit * bc = new BattleCruiser;
	bc->move(666, 77);
	delete bc;
}
