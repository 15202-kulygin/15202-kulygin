//
// Created by glavak on 08.11.16.
//

#ifndef PRISONERS_CONTROLLERTOURNAMENT_H
#define PRISONERS_CONTROLLERTOURNAMENT_H


#include "Controller.h"

class ControllerTournament : public Controller
{
public:
    ControllerTournament(
            const ScoreMatrix & matrix,
            const std::string & strategiesConfigPath,
            const std::vector<std::string> & names,
            int steps)
            : Controller(matrix, strategiesConfigPath, names, steps)
    {}

    virtual void doJob() override;

private:
    void tournamentTick();
};


#endif //PRISONERS_CONTROLLERTOURNAMENT_H
