//
// Created by glavak on 07.10.16.
//

#include <iostream>
#include "BattleCruiser.h"

namespace
{
    Unit * createBC()
    {
        return new BattleCruiser;
    }

    bool registered = Factory::getInstance()->reg("battlecruiser", createBC);
}

BattleCruiser::~BattleCruiser()
{
    std::cout << "BattleCruiser destructor" << std::endl;
}

void BattleCruiser::move(int x, int y)
{
    std::cout << "BattleCruiser::move" << std::endl;
}

void BattleCruiser::attack(int x, int y)
{
    std::cout << "BattleCruiser::attack" << std::endl;
}