#ifndef BATTLECRUISER_H
#define BATTLECRUISER_H

#include "unit.h"

class BattleCruiser : public Unit {
	public:
		~BattleCruiser () override;
		virtual void move(int x, int y) override;
		virtual void attack(int x, int y) override;

};

#endif