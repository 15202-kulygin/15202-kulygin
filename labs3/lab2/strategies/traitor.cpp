#include "../factory.h"
#include <iostream>


class Traitor : public Strategy {
	public:
		Traitor ();
		~Traitor () override;
		virtual Action make_action(Action ** history, int history_size, int tick) override;
};

Strategy * createTraitor(){
	return new Traitor;
}

static bool ok = Factory::getInstance()->regist3r(
	"traitor", createTraitor);


Traitor::Traitor()
{
	//std::cout << "Traitor constructor" << std::endl;
	name = "Traitor";
	score = 0;
}
Traitor::~Traitor()
{
	//std::cout << "Traitor destructor" << std::endl;
}
Action Traitor::make_action(Action ** history, int history_size, int tick)
{
	return DEFECT;
}
