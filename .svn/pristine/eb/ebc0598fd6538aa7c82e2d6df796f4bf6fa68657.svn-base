#include "factory.h"
#include <iostream>


class Traitor : public Strategy {
	public:
		Traitor ();
		~Traitor () override;
		virtual void print_score() override;
		virtual int get_score() override;
		virtual std::string get_name() override;
		virtual Action make_action(Action ** history, int tick) override;
		virtual void add_score(int value) override;

};

Strategy * createTraitor(){
	return new Traitor;
}

static bool ok = Factory::getInstance()->regist3r(
	"traitor", createTraitor);


Traitor::Traitor()
{
	std::cout << "Traitor constructor" << std::endl;
	name = "Traitor";
	score = 0;
}
Traitor::~Traitor()
{
	std::cout << "Traitor destructor" << std::endl;
}
void Traitor::print_score() 
{
	std::cout << "Traitor score: " << score << std::endl;
}
int Traitor::get_score() 
{
	return score;
}
std::string Traitor::get_name()
{
	return name;
}
Action Traitor::make_action(Action ** history, int tick)
{
	return DEFECT;
}
void Traitor::add_score(int value) 
{
	score += value;
}