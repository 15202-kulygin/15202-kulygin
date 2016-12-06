//
// Created by glavak on 08.11.16.
//

#include "ControllerTournament.h"

void ControllerTournament::tournamentTick()
{
    for (size_t i = 0; i < strategies.size() - 2; i++)
    {
        for (size_t j = i + 1; j < strategies.size() - 1; j++)
        {
            for (size_t k = j + 1; k < strategies.size(); k++)
            {
                std::cout << "Match '" << i << "vs" << j << "vs" << k << "':" << std::endl;
                this->fight(i, j, k);
                this->printState();
            }
        }
    }
}


void ControllerTournament::doJob()
{
    for (int i = 0; i < steps; i++)
    {
        tournamentTick();
    }
}
