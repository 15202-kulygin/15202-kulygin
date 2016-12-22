#include "game.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

Game::Game() 
{

}
Game::Game(Strategy * s1, Strategy * s2, Strategy * s3)
{
	ticks = DEFAULT_TICKS_AMOUNT;
	history_size = ticks;
	history = new Action * [history_size];
	for (int i = 0; i < history_size; ++i)
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
	game_mode = DETAILED;
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
	history_size = 0;
}
void Game::play_game()
{
	if (game_mode == DETAILED)
	{
		ticks = 0;
		detailed_game();
	}
	else if (game_mode == FAST)
	{
		fast_game();
	}
	else 
	{
		tournament_game();
	}
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

void Game::make_step(int n)
{
	//std::cout << history_size << " cur hist size" << std::endl;
	for (int i = 0; i < n; ++i)
	{
		if (ticks + 1 > history_size)
		{
			realloc_history();				
		}
		Action action1 = strategy1->make_action(history, i);
		Action action2 = strategy2->make_action(history, i);
		Action action3 = strategy3->make_action(history, i);
		history[ticks][0] = action1;
		history[ticks][1] = action2;
		history[ticks][2] = action3;
		int index = 4 * (int)history[ticks][0] + 2 * (int)history[ticks][1] + 1 * (int)history[ticks][2];
		strategy1->add_score(rules[index][0]);
		strategy2->add_score(rules[index][1]);
		strategy3->add_score(rules[index][2]);
		ticks++;
		std::cout << std::endl << std::endl << "Tick " << ticks << " played." << std::endl << "Score: ";
		std::cout << strategy1->get_name() << " " << rules[index][0] << ", ";
		std::cout << strategy2->get_name() << " " << rules[index][1] << ", ";
		std::cout << strategy3->get_name() << " " << rules[index][2];
		std::cout << std::endl << "Current score: ";
		std::cout << strategy1->get_name() << " " << strategy1->get_score() << ", ";
		std::cout << strategy2->get_name() << " " << strategy2->get_score() << ", ";
		std::cout << strategy3->get_name() << " " << strategy3->get_score() << std::endl;
		std::cout << "History: " << std::endl;
		print_history();
		std::cout << std::endl;
	}
}

void Game::realloc_history()
{
	int old_size = history_size;
	history_size *= 2;
	Action ** temp = new Action * [history_size];
	for (int i = 0; i < old_size; ++i)
	{
		temp[i] = new Action [3];
		for (int j = 0; j < 3; ++j)
		{
			temp[i][j] = history[i][j];
		}
		delete [] history[i];
	}
	delete [] history;
	for (int i = old_size; i < history_size; ++i)
	{
		temp[i] = new Action [3];
		for (int j = 0; j < 3; ++j)
		{
			temp[i][j] = UNDEFINED;
		}
	}
	history = temp;
}

void Game::detailed_game()
{
	std::cout << "Game in detailed mode began." << std::endl;
	ticks = 0;
	while(true)
	{
		char * str = (char *) calloc (100, sizeof(char));
		gets(str);
		if ((0 != strcmp("quit", str)) && (0 != strncmp("tick", str, 4)))
		{
			std::cout << "Wrong command format. Put it int like \"tick\" or \"tick n\", or \"quit\", where n is an integer value" << std::endl;			
		}
		else if (0 == strcmp("tick", str))
		{
			make_step(1);
		}
		else if (0 == strcmp("quit", str))
		{
			std::cout << std::endl << std::endl << "Game played." << std::endl << "Score: ";
			std::cout << strategy1->get_name() << " " << strategy1->get_score() << ", ";
			std::cout << strategy2->get_name() << " " << strategy2->get_score() << ", ";
			std::cout << strategy3->get_name() << " " << strategy3->get_score() << std::endl;
			std::cout << "History: " << std::endl;
			Game::print_history();
			std::cout << std::endl << std::endl;
			free(str);
			break;
		}
		else
		{
			int ind = 4;
			while (!isdigit(str[ind]))
			{
				++ind;
			}
				char * number = (char *) calloc (100, sizeof(char));
			int num_ind = 0;
			while(isdigit(str[ind]))
			{
				number[num_ind++] = str[ind++];
			}
			int n = atoi(number);
			free(number);
			make_step(n);
		}
	}
}

void Game::fast_game()
{
	int n = ticks;
	ticks = 0;
	make_step(n);
}

void Game::tournament_game()
{

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