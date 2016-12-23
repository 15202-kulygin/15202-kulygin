#include "../factory.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


class Random : public Strategy {
	public:
		Random ();
		~Random () override;
		virtual Action make_action(std::vector<Action> & history, int history_size, int tick) override;
};

Strategy * createRandom(){
	return new Random;
}

static bool ok = Factory::getInstance()->regist3r(
	"random", createRandom);


Random::Random()
{
	//std::cout << "Random constructor" << std::endl;
	name = "Random";
	score = 0;
}
Random::~Random()
{
	//std::cout << "Random destructor" << std::endl;
}
Action Random::make_action(std::vector<Action> & history, int history_size, int tick)
{
	srand(time(0));
	return (Action)(rand()%2);
}