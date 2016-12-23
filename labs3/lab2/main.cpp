#include <memory>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "arguments.h"
#include "factory.h"
#include "strategy.h"
#include "game.h"

//g++ -std=c++11 main.cpp arguments.cpp game.cpp ./strategies/traitor.cpp ./strategies/doubtful.cpp ./strategies/cooperator.cpp -o out.exe


int main (int argc, char ** argv)
{
	Factory * f = Factory::getInstance();
	if (4 > argc)
	{
		std::cerr << "Provide strategies name" << std::endl;
		return -1;
	}
	std::string strategy_id1 = argv[1];
	std::string strategy_id2 = argv[2];
	std::string strategy_id3 = argv[3];
	Strategy * s1(f->create(strategy_id1)); //??????
	Strategy * s2(f->create(strategy_id2)); // unique
	Strategy * s3(f->create(strategy_id3));
	Game * g = new Game(s1, s2, s3);
	for (int i = 4; i < argc; ++i) // переделать под C
	{
		if (!strncmp(argv[i], "--matrix=", 9)) // matrix argument
		{
			
			std::string file_name = get_argument_value(argv[i]);
			FILE * input = fopen(file_name.c_str(), "r");
			if (nullptr == input)
			{
				std::cerr << std::endl << std::endl << "Can't open matrix file" << std::endl;
				fclose(input);
				delete s1;
				delete s2;
				delete s3;
				delete g;
				return -1;
			}
			int matrix[8][3];
			if (8 != get_matrix_from_file(input, matrix))
			{
				std::cerr << std::endl << std::endl << "The matrix file is incorrect" << std::endl;
				fclose(input);
				return -1;
			}
			fclose(input);
			g->load_rules(matrix);
			/*
			for (int a = 0; a < 8; ++a)
			{
				for (int b = 0; b < 3; ++b)
				{
					std::cout << matrix[a][b] << " ";
				}
				std::cout << std::endl;
			}*/
		}
		else if (!strncmp((argv[i]), "--steps=", 8)) //number of ticks argument
		{
			std::string value = get_argument_value(argv[i]);
			if (0 == value.length())
			{
				std::cerr << std::endl << std::endl << "Wrong steps format" << std::endl;
				delete s1;
				delete s2;
				delete s3;
				delete g;
				return -1;
			}
			int t = atoi(value.c_str());
			if (0 > t)
			{
				std::cerr << std::endl << std::endl << "Wrong steps format" << std::endl;
				delete s1;
				delete s2;
				delete s3;
				delete g;
				return -1;
			}
			g->load_ticks(t);
		}
		else if (!strncmp((argv[i]), "--mode=", 7)) //game mode argument
		{
			std::string mode_name = get_argument_value(argv[i]);
			if (("detailed" != mode_name) && ("fast" != mode_name) && ("tournament" != mode_name))
			{
				std::cerr << std::endl << std::endl << "Wrong mode format" << std::endl;
				delete s1;
				delete s2;
				delete s3;
				delete g;
				return -1;
			}
			else if ("detailed" == mode_name)
			{
				g->load_mode(DETAILED);
			}
			else if ("fast" == mode_name)
			{
				g->load_mode(FAST);
			}
			else if ("tournament" != mode_name)
			{
				g->load_mode(TOURNAMENT);
			}
			
		}


	}
	g->play_game();
	delete s1;
	delete s2;
	delete s3;
	delete g;
}