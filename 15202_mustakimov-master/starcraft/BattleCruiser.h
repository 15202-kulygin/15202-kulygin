//
// Created by glavak on 07.10.16.
//

#ifndef STARCRAFT_BATTLECRUISER_H
#define STARCRAFT_BATTLECRUISER_H

#include "Unit.h"
#include "Factory.h"

class BattleCruiser : public Unit
{
public:
    ~BattleCruiser() override;

    void move(int x, int y) override;

    void attack(int x, int y) override;
};

#endif //STARCRAFT_BATTLECRUISER_H
