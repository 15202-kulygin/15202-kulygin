#include "game.h"
#include <iostream>

Game::Game() 
{

}
Game::Game(Strategy * s1, Strategy * s2, Strategy * s3)
{
	for (int i = 0; i < TICKS_AMOUNT; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			history[i][j] = UNDEFINED;
		}
	}
	rules[0][0] = 4;
	rules[0][1] = 4;
	rules[0][2] = 4;

	rules[1][0] = 2;
	rules[1][1] = 2;
	rules[1][2] = 5;

	rules[2][0] = 2;
	rules[2][1] = 5;
	rules[2][2] = 2;

	rules[3][0] = 5;
	rules[3][1] = 2;
	rules[3][2] = 2;

	rules[4][0] = 0;
	rules[4][1] = 3;
	rules[4][2] = 3;

	rules[5][0] = 3;
	rules[5][1] = 0;
	rules[5][2] = 3;

	rules[6][0] = 3;
	rules[6][1] = 3;
	rules[6][2] = 0;

	rules[7][0] = 1;
	rules[7][1] = 1;
	rules[7][2] = 1;
	strategy1 = s1;
	strategy2 = s2;
	strategy3 = s3;
}

Game::~Game()
{
	strategy1 = 0;
	strategy2 = 0;
	strategy3 = 0;
}
void Game::play_game(int ticks)
{
	for (int i = 0; i < ticks; ++i)
	{
		Action action1 = strategy1->make_action((Action **)history, i);
		Action action2 = strategy2->make_action((Action **)history, i);
		Action action3 = strategy3->make_action((Action **)history, i);
		history[i][0] = action1;
		history[i][1] = action2;
		history[i][2] = action3;
		int index = 4 * (int)history[i][0] + 2 * (int)history[i][1] + 1 * (int)history[i][2];
 		int * scores = new int [3];
 		scores[0] = rules[index][0];
 		scores[1] = rules[index][1];
 		scores[2] = rules[index][2];
 	
 		//std::cout << "CHECK " << index << std::endl;

		strategy1->add_score(scores[0]);
		strategy2->add_score(scores[1]);
		strategy3->add_score(scores[2]);
		delete scores;
	}
	std::cout << std::endl << std::endl << "Game played." << std::endl << "Score: ";
	std::cout << strategy1->get_name() << " " << strategy1->get_score() << ", ";
	std::cout << strategy2->get_name() << " " << strategy2->get_score() << ", ";
	std::cout << strategy3->get_name() << " " << strategy3->get_score() << std::endl;
	std::cout << "History: " << std::endl;
	Game::print_history();
	std::cout << std::endl << std::endl;
	
}
void Game::print_history()
{
	for (int i = 0; i < TICKS_AMOUNT; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << history[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}



/*
з1 з2 з3     з1 з2 з3
 С  С  С  =>  4  4  4  //заключённые 1, 2 и 3 получают по 4 очка  
 C  C  D  =>  2  2  5
 C  D  C  =>  2  5  2
 D  C  C  =>  5  2  2
 C  D  D  =>  0  3  3 
 D  C  D  =>  3  0  3
 D  D  C  =>  3  3  0
 D  D  D  =>  1  1  1  
 */