#include "game.h"
#include <iostream>

Game::Game() 
{

}
Game::Game(Strategy * s1, Strategy * s2, Strategy * s3)
{
	ticks = DEFAULT_TICKS_AMOUNT;
	history = new Action * [ticks];
	for (int i = 0; i < ticks; ++i)
	{
		history[i] = new Action [3];
		for (int j = 0; j < 3; ++j)
		{
			history[i][j] = UNDEFINED;
		}
	}
	strategy1 = s1;
	strategy2 = s2;
	strategy3 = s3;
}

Game::~Game()
{
	for (int i = 0; i < ticks; ++i)
	{
		delete [] history[i];
	}
	delete [] history;
	strategy1 = 0;
	strategy2 = 0;
	strategy3 = 0;
	ticks = 0;
}
void Game::play_game()
{
	for (int i = 0; i < ticks; ++i)
	{
		Action action1 = strategy1->make_action(history, i);
		Action action2 = strategy2->make_action(history, i);
		Action action3 = strategy3->make_action(history, i);
		history[i][0] = action1;
		history[i][1] = action2;
		history[i][2] = action3;
		int index = 4 * (int)history[i][0] + 2 * (int)history[i][1] + 1 * (int)history[i][2];
		strategy1->add_score(rules[index][0]);
		strategy2->add_score(rules[index][1]);
		strategy3->add_score(rules[index][2]);
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
	for (int i = 0; i < ticks; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cout << history[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}
int Game::get_ticks_amount()
{
	return ticks;
}
void Game::load_rules(int matrix[8][3])
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			rules[i][j] = matrix[i][j];
		}
	}
}
void Game::load_ticks(int to_load)
{
	for (int i = 0; i < ticks; ++i)
	{
		delete [] history[i];
	}
	delete [] history;
	ticks = to_load;
	history = new Action * [ticks];
	for (int i = 0; i < ticks; ++i)
	{
		history[i] = new Action [3];
		for (int j = 0; j < 3; ++j)
		{
			history[i][j] = UNDEFINED;
		}
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