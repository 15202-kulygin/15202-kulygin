#ifndef GAME_H
#define GAME_H

#include "strategy.h"
#include <vector>

class Game {
	private:
		static const int DEFAULT_TICKS_AMOUNT = 5;
		int ticks;
		std::vector<std::vector<int>> rules { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
		Action ** history;
		Strategy * strategy1;
		Strategy * strategy2;
		Strategy * strategy3;
	public:
		Game();
		Game(Strategy * s1, Strategy * s2, Strategy * s3);
		~Game();
		void play_game();
		void print_history();
		int get_ticks_amount();
		void load_rules(int matrix[8][3]);
		void load_ticks(int to_load);
};


#endif