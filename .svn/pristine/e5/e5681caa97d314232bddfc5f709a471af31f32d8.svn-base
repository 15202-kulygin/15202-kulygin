#include "factory.h"
#include <iostream>


class Doubtful : public Strategy {
	public:
		Doubtful ();
		~Doubtful () override;
		virtual void print_score() override;
		virtual int get_score() override;
		virtual std::string get_name() override;
		virtual Action make_action(Action ** history, int tick) override;
		virtual void add_score(int value) override;

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
void Doubtful::print_score() 
{
	std::cout << "Doubtful score: " << score << std::endl;
}
int Doubtful::get_score() 
{
	return score;
}
std::string Doubtful::get_name()
{
	return name;
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
void Doubtful::add_score(int value) 
{
	score += value;
}