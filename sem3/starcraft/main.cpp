#include "unit.h"
#include "battlecruiser.h"
#include "zergling.h"
#include <iostream>
#include <string>

using namespace std;

/*Unit * createUnit (const string& id)
{
	if ("battlecruiser" == id)
	{
		return new BattleCruiser;
	}
	else if ("zergling" == id)
	{
		return new Zergling;
	}
}*/

int main ()
{
	string unit_id = "battlecruiser";

	Unit * bc = new BattleCruiser;
	bc->move(666, 77);
	delete bc;
}
