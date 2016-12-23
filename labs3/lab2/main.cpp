#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <fstream>
#include "arguments.h"
#include "factory.h"
#include "strategy.h"
#include "game.h"

//g++ -std=c++11 main.cpp arguments.cpp game.cpp ./strategies/traitor.cpp ./strategies/doubtful.cpp ./strategies/cooperator.cpp ./strategies/adaptive.cpp ./strategies/random.cpp -o out.exe -ggdb


int main (int argc, char ** argv)
{
	Factory * f = (Factory::getInstance());
	if (4 > argc)
	{
		std::cerr << "Provide strategies name" << std::endl;
		return -1;
	}
	std::string strategy_id1 = argv[1];
	std::string strategy_id2 = argv[2];
	std::string strategy_id3 = argv[3];
	std::unique_ptr<Strategy> s1(f->create(strategy_id1));
	std::unique_ptr<Strategy> s2(f->create(strategy_id2)); 
	std::unique_ptr<Strategy> s3(f->create(strategy_id3));
	if ((nullptr == s1) || (nullptr == s2) || (nullptr == s3))
	{
		std::cerr << "Wrong strategy name";
		return -1;
	}
	std::unique_ptr<Game> gptr = std::unique_ptr<Game>(new Game(s1.get(), s2.get(), s3.get()));
	Game * g = gptr.get();
	int is_tournament = 0;
	for (int i = 0; i < argc; ++i) // разбор аргументов
	{
		if (!strncmp(argv[i], "--matrix=", 9)) // matrix argument
		{
			
			std::string file_name = get_argument_value(argv[i]);
			FILE * input = fopen(file_name.c_str(), "r");
			if (nullptr == input)
			{
				std::cerr << std::endl << std::endl << "Can't open matrix file" << std::endl;
				fclose(input);
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
			
		}
		else if (!strncmp((argv[i]), "--steps=", 8)) //number of ticks argument
		{
			std::string value = get_argument_value(argv[i]);
			if (0 == value.length())
			{
				std::cerr << std::endl << std::endl << "Wrong steps format" << std::endl;
				return -1;
			}
			int t = atoi(value.c_str());
			if (0 > t)
			{
				std::cerr << std::endl << std::endl << "Wrong steps format" << std::endl;
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
			else if ("tournament" == mode_name)
			{
				g->load_mode(TOURNAMENT);
				is_tournament = 1;
			}
		}
	}
	if (0 == is_tournament) 
	{
		g->play_game();
	}
	else //турнирный режим
	{
		std::cout << "Enter name of the file with some additional strategies" << std::endl;
		std::string file_name;
		std::getline(std::cin, file_name);
		std::ifstream file(file_name); 
		std::string id; 
		std::vector<Strategy *> strategy_list;
		strategy_list.reserve(10);
		strategy_list[0] = s1.get();
		int ind = 1;
		int chk = 0;
		for (int i = 0; i < ind; ++i)
		{
			if (strategy_list[i]->get_name() == s2.get()->get_name())
			{
				chk = -1;
				break;
			}
		}
		if (0 == chk)
    	{
 			strategy_list[ind] = s2.get();
    	    ++ind;
    	}
    	chk = 0;
		for (int i = 0; i < ind; ++i)
		{
			if (strategy_list[i]->get_name() == s3.get()->get_name())
			{
				chk = -1;
				break;
			}
		}
		if (0 == chk)
    	{
 			strategy_list[ind] = s3.get();
    	    ++ind;
    	}
    	while (file >> id)
    	{
    		
    		Strategy * s(f->create(id));
    		if (nullptr == s)
    		{
    			std::cout << "Wrong strategy name in the file" << std::endl;
    			return -1;
    		}
    		else
    		{
    			int check = 0;
    			for (int i = 0; i < ind; ++i)
				{
					if (strategy_list[i]->get_name() == s->get_name())
					{
						check = -1;
						break;
					}
				}
	   			if (0 == check)
    			{
   					strategy_list[ind] = s;
  					++ind;
    			}
    			else
    			{
    				delete s;
    			}
   			}
		}
    			/*for (int i = 0; i < ind; ++i)
    			{
    				std::cout << strategy_list[i]->get_name() << std::endl;
    			}*/
    	for (int i = 0; i < ind - 2; ++i)
    	{
    		for (int j = i + 1; j < ind - 1; ++j)
    		{
    			for (int k = j + 1; k < ind; ++k)
    			{
    				g->load_strategies(strategy_list[i], strategy_list[j], strategy_list[k]);
    				g->play_game();
    			}
    		}
    	}
 	}
}