//
// Created by glavak on 14.10.16.
//

#include "SiegeTank.h"
#include "Unit.h"
#include "Factory.h"


namespace
{
    Unit * createSiegeTank()
    {
        return new SiegeTank;
    }

    bool registered = Factory::getInstance()->reg("siegetank", createSiegeTank);
}

void SiegeTank::move(int x, int y)
{
    std::cout << "SiegeTank::move" << std::endl;
}

void SiegeTank::attack(int x, int y)
{
    std::cout << "SiegeTank::attack" << std::endl;
}

SiegeTank::~SiegeTank()
{
    std::cout << "SiegeTank dtor" << std::endl;
}
