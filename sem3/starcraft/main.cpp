#include <iostream>
#include <string>
#include <memory>
#include "unit.h"
#include "battlecruiser.h"
#include "zergling.h"
#include "factory.h"


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





int main (int argc, char ** argv)
{
	Factory <Unit, std::string, Unit * (*) ()> * f = Factory<Unit, std::string, Unit*(*)()>::getInstance();
	
	if (2 != argc)
	{
		cerr << "Provide unit name" << std::endl;
		return -1;
	}
	std::string unit_id = argv[1];

	std::unique_ptr<Unit> u(f->create(unit_id));
	u->move(666, 77);

}
