#include "factory.h"
#include <iostream>

using namespace std;

class SiegeTank : public Unit {
	public:
		~SiegeTank () override;
		virtual void move(int x, int y) override;
		virtual void attack(int x, int y) override;

};

Unit * createTank(){
	return new SiegeTank;
}

static bool ok = Factory::getInstance()->regist3r(
	"siegetank", createTank);



SiegeTank::~SiegeTank()
{
	cout << "SiegeTank destructor" << endl;
}
void SiegeTank::move(int x, int y) 
{
	cout << "SiegeTank moved!" << endl;
}
void SiegeTank::attack(int x, int y)
{
	cout << "SiegeTank attacked!";
}