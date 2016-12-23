#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include <iostream>

typedef enum Action {
	COOPERATE = 0, DEFECT = 1, UNDEFINED = 2
} Action;

class Strategy {
	protected:
		int score;
		std::string name;
	public:
		Strategy() {
			score = 0;
			name = " ";
		}
		virtual ~Strategy () {};
		void print_score() 
		{
			std::cout << name << " score: " << score << std::endl;
		}
		int get_score() 
		{
			return score;
		}
		std::string get_name() 
		{
			return name;
		}
		void add_score(int value)
		{
			score += value;
		}
		virtual Action make_action(Action ** history, int history_size, int tick) = 0;
		
};

#endif