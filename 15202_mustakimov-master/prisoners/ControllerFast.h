//
// Created by glavak on 07.11.16.
//

#ifndef PRISONERS_CONTROLLERFAST_H
#define PRISONERS_CONTROLLERFAST_H


#include "Controller.h"

class ControllerFast : public Controller
{
public:
    ControllerFast(
            const ScoreMatrix & matrix,
            const std::string & strategiesConfigPath,
            const std::vector<std::string> & names,
            int steps)
            : Controller(matrix, strategiesConfigPath, names, steps)
    { }

    virtual void doJob() override;
};


#endif //PRISONERS_CONTROLLERFAST_H
