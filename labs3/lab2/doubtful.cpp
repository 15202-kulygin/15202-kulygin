#include "factory.h"
#include <iostream>


class Doubtful : public Strategy {
	public:
		Doubtful ();
		~Doubtful () override;
		virtual Action make_action(Action ** history, int tick) override;
};

Strategy * createDoubtful(){
	return new Doubtful;
}

static bool ok = Factory::getInstance()->regist3r(
	"doubtful", createDoubtful);


Doubtful::Doubtful()
{
	std::cout << "Doubtful constructor" << std::endl;
	name = "Doubtful";
	score = 0;
}
Doubtful::~Doubtful()
{
	std::cout << "Doubtful destructor" << std::endl;
}
Action Doubtful::make_action(Action ** history, int tick)
{
	if (0 == tick % 2)
	{
		return COOPERATE;
	}
	else
	{
		return DEFECT;
	}
}
