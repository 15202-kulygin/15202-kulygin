#include "../factory.h"
#include <iostream>


class Cooperator : public Strategy {
	public:
		Cooperator ();
		~Cooperator () override;
		virtual Action make_action(Action ** history, int tick) override;
};

Strategy * createCooperator(){
	return new Cooperator;
}

static bool ok = Factory::getInstance()->regist3r(
	"cooperator", createCooperator);


Cooperator::Cooperator()
{
	//std::cout << "Cooperator constructor" << std::endl;
	name = "Cooperator";
	score = 0;
}
Cooperator::~Cooperator()
{
	//std::cout << "Cooperator destructor" << std::endl;
}
Action Cooperator::make_action(Action ** history, int tick)
{
	return COOPERATE;
}