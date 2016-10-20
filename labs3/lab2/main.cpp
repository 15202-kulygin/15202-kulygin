#include <memory>
#include <iostream>
#include "factory.h"
#include "strategy.h"
#include "game.h"


int main (int argc, char ** argv)
{
	Factory * f = Factory::getInstance();
	
	if (4 != argc)
	{
		std::cerr << "Provide strategies name" << std::endl;
		return -1;
	}
	std::string strategy_id1 = argv[1];
	std::string strategy_id2 = argv[2];
	std::string strategy_id3 = argv[3];
	Strategy * s1(f->create(strategy_id1));
	Strategy * s2(f->create(strategy_id2));
	Strategy * s3(f->create(strategy_id3));
	Game * g = new Game(s1, s2, s3);
	g->play_game(TICKS_AMOUNT);
	delete s1;
	delete s2;
	delete s3;
	delete g;
}