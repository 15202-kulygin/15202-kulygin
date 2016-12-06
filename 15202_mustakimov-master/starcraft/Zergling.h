//
// Created by glavak on 07.10.16.
//

#ifndef STARCRAFT_ZERGLING_H
#define STARCRAFT_ZERGLING_H


#include "Unit.h"

class Zergling : public Unit
{
public:
    ~Zergling() override;

    void move(int x, int y) override;

    void attack(int x, int y) override;
};


#endif //STARCRAFT_ZERGLING_H
