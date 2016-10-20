#ifndef GAME_H
#define GAME_H

#include "strategy.h"

#define TICKS_AMOUNT 5

class Game {
	private:
		int rules[8][3];
		Action history[TICKS_AMOUNT][3];
		Strategy * strategy1;
		Strategy * strategy2;
		Strategy * strategy3;
	public:
		Game();
		Game(Strategy * s1, Strategy * s2, Strategy * s3);
		~Game();
		void play_game(int ticks);
		void print_history();
};


#endif