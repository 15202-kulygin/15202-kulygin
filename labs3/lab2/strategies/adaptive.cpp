#include "../factory.h"
#include <iostream>


class Adaptive : public Strategy {
	public:
		Adaptive ();
		~Adaptive () override;
		virtual Action make_action(std::vector<Action> & history, int history_size, int tick) override;
};

Strategy * createAdaptive(){
	return new Adaptive;
}

static bool ok = Factory::getInstance()->regist3r(
	"adaptive", createAdaptive);


Adaptive::Adaptive()
{
	//std::cout << "Adaptive constructor" << std::endl;
	name = "Adaptive";
	score = 0;
}
Adaptive::~Adaptive()
{
	//std::cout << "Adaptive destructor" << std::endl;
}
Action Adaptive::make_action(std::vector<Action> & history, int history_size, int tick)
{
	float cooperate_percent = 0.0;

	for (int i = 0; i < tick; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (history[3*i + j] == COOPERATE)
			{
				cooperate_percent += 1.0;
			}
		}
	}
	cooperate_percent /= (tick-1)*3;
	if (cooperate_percent > (float)(0.85))
	{
		return COOPERATE;
	}
	else
	{
		return DEFECT;
	}
}