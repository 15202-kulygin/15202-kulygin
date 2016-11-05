#include "factory.h"
#include <iostream>


class Cooperator : public Strategy {
	public:
		Cooperator ();
		~Cooperator () override;
		virtual void print_score() override;
		virtual int get_score() override;
		virtual std::string get_name() override;
		virtual Action make_action(Action ** history, int tick) override;
		virtual void add_score(int value) override;

};

Strategy * createCooperator(){
	return new Cooperator;
}

static bool ok = Factory::getInstance()->regist3r(
	"cooperator", createCooperator);


Cooperator::Cooperator()
{
	std::cout << "Cooperator constructor" << std::endl;
	name = "Cooperator";
	score = 0;
}
Cooperator::~Cooperator()
{
	std::cout << "Cooperator destructor" << std::endl;
}
void Cooperator::print_score() 
{
	std::cout << "Cooperator score: " << score << std::endl;
}
int Cooperator::get_score() 
{
	return score;
}
std::string Cooperator::get_name()
{
	return name;
}
Action Cooperator::make_action(Action ** history, int tick)
{
	return COOPERATE;
}
void Cooperator::add_score(int value) 
{
	score += value;
}