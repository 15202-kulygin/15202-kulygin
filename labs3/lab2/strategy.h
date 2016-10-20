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
		virtual void print_score() = 0;
		virtual int get_score() = 0;
		virtual std::string get_name() = 0;
		virtual Action make_action(Action ** history, int tick) = 0;
		virtual void add_score(int value) = 0;
};

#endif