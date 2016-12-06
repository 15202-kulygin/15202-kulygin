//
// Created by glavak on 14.10.16.
//

#ifndef STARCRAFT_SIEGETANK_H
#define STARCRAFT_SIEGETANK_H


#include "Unit.h"

class SiegeTank : public Unit
{
public:
    ~SiegeTank() override;

    void move(int x, int y) override;

    void attack(int x, int y) override;
};


#endif //STARCRAFT_SIEGETANK_H
