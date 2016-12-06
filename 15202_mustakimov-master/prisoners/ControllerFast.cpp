//
// Created by glavak on 07.11.16.
//

#include "ControllerFast.h"

void ControllerFast::doJob()
{
    std::cout << "Last turn:" << std::endl;
    for (int i = 0; i < steps; i++)
    {
        fight(0, 1, 2);
    }
    printState();
}
