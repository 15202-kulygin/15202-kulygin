//
// Created by glavak on 07.10.16.
//

#include <iostream>
#include "Zergling.h"
#include "Factory.h"

namespace
{
    Unit * createZergling()
    {
        return new Zergling;
    }

    bool registered = Factory::getInstance()->reg("zergling", createZergling);
}

void Zergling::move(int x, int y)
{
    std::cout << "Zergling::move" << std::endl;
}

void Zergling::attack(int x, int y)
{
    std::cout << "Zergling::attack" << std::endl;
}

Zergling::~Zergling()
{
    std::cout << "Zergling dtor" << std::endl;
}
