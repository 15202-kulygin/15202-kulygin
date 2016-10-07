#ifndef ZERGLING_H
#define ZERGLING_H

#include "unit.h"

using namespace std;

class Zergling : public Unit {
	public:
		~Zergling () override;
		virtual void move(int x, int y) override;
		virtual void attack(int x, int y) override;

};

#endif