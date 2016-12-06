//
// Created by glavak on 07.10.16.
//

#ifndef STARCRAFT_UNIT_H
#define STARCRAFT_UNIT_H

#include <iostream>

class Unit
{
public:
    virtual ~Unit()
    {
        std::cout << "Unit dtor" << std::endl;
    }

    virtual void move(int x, int y) = 0;

    virtual void attack(int x, int y) = 0;
};

#endif //STARCRAFT_UNIT_H
