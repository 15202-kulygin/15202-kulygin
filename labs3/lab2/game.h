#ifndef GAME_H
#define GAME_H

#include "strategy.h"
#include <vector>

typedef enum Mode {
	DETAILED, FAST, TOURNAMENT 
} Mode;

class Game {
	private:
		static const int DEFAULT_TICKS_AMOUNT = 5;
		int ticks;
		int history_size;
		std::vector<int> rules = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		std::vector<Action> history;
		Strategy * strategy1;
		Strategy * strategy2;
		Strategy * strategy3;
		Mode game_mode;
	public:
		Game();
		Game(Strategy * s1, Strategy * s2, Strategy * s3);
		~Game();
		void play_game();
		void print_history();
		int get_ticks_amount();
		void load_rules(int matrix[8][3]);
		void load_ticks(int to_load);
		void load_mode(Mode mode) {game_mode = mode;}
		void make_step(int n);
		void realloc_history();
		void detailed_game();
		void fast_game();
		void tournament_game();
		void load_strategies(Strategy * s1, Strategy * s2, Strategy * s3);

};


#endif