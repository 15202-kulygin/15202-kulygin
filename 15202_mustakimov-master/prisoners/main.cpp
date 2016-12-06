#include <iostream>
#include <vector>
#include "Controller.h"
#include "Arguments.h"
#include "ControllerTournament.h"
#include "ControllerFast.h"
#include "ControllerDetailed.h"


int main(int argc, char * argv[])
{
    Arguments arguments(argc, argv);
    srand((unsigned int) time(nullptr));

    if (arguments.mode == Modes::Unset)
    {
        if (arguments.names.size() == 3)
        {
            arguments.mode = Modes::Detailed;
        }
        else
        {
            arguments.mode = Modes::Tournament;
        }
    }

    ScoreMatrix matrix;
    if (arguments.matrixFile.compare("") != 0)
    {
        matrix.loadFromFile(arguments.matrixFile);
    }
    // unique_ptr
    Controller * controller;

    if (arguments.mode == Modes::Tournament)
    {
        controller = new ControllerTournament(matrix, arguments.configDirectory, arguments.names, arguments.steps);
    }
    else if(arguments.mode == Modes::Fast)
    {
        controller = new ControllerFast(matrix, arguments.configDirectory, arguments.names, arguments.steps);
    }
    else if(arguments.mode == Modes::Detailed)
    {
        controller = new ControllerDetailed(matrix, arguments.configDirectory, arguments.names, arguments.steps);
    }

    controller->doJob();

    std::cout << std::endl;
    controller->printWinner();

    delete controller;

    return 0;
}