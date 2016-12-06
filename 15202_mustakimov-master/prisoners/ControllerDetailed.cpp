//
// Created by glavak on 08.11.16.
//

#include "ControllerDetailed.h"

void ControllerDetailed::tick(int count)
{
    for (int i = 0; i < count; i++)
    {
        fight(0, 1, 2);
    }
}

void ControllerDetailed::doJob()
{
    std::string command;
    std::getline(std::cin, command);
    while (command.compare("quit") != 0)
    {
        if (command.compare("tick") == 0)
        {
            tick(1);
            printState();
        }
        else if (command.compare(0, 5, "tick ") == 0)
        {
            command = command.substr(5);
            tick(atoi(command.c_str()));
            printState();
        }
        std::getline(std::cin, command);
    }
}
