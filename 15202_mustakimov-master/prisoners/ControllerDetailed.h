//
// Created by glavak on 08.11.16.
//

#ifndef PRISONERS_CONTROLLERDETAILED_H
#define PRISONERS_CONTROLLERDETAILED_H


#include "Controller.h"

class ControllerDetailed : public Controller
{
public:
    ControllerDetailed(
            const ScoreMatrix & matrix,
            const std::string & strategiesConfigPath,
            const std::vector<std::string> & names,
            int steps)
            : Controller(matrix, strategiesConfigPath, names, steps)
    {}

    virtual void doJob() override;

private:
    void tick(int count);
};


#endif //PRISONERS_CONTROLLERDETAILED_H
