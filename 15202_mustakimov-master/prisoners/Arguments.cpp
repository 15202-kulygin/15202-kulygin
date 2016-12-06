//
// Created by glavak on 20.10.16.
//

#include "Arguments.h"

Arguments::Arguments(int argc, char ** argv)
{
    std::string modePrefix("--mode=");
    std::string stepsPrefix("--steps=");
    std::string configsPrefix("--configs=");
    std::string matrixPrefix("--matrix=");

    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);

        if (arg.compare(0, modePrefix.size(), modePrefix) == 0)
        {
            arg = arg.substr(modePrefix.size());
            if (arg.compare("detailed") == 0)
            {
                mode = Modes::Detailed;
            }
            else if (arg.compare("fast") == 0)
            {
                mode = Modes::Fast;
            }
            else if (arg.compare("tournament") == 0)
            {
                mode = Modes::Tournament;
            }
        }
        else if (arg.compare(0, stepsPrefix.size(), stepsPrefix) == 0)
        {
            arg = arg.substr(stepsPrefix.size());
            steps = atoi(arg.c_str());
        }
        else if (arg.compare(0, configsPrefix.size(), configsPrefix) == 0)
        {
            arg = arg.substr(configsPrefix.size());
            configDirectory = arg.c_str();
        }
        else if (arg.compare(0, matrixPrefix.size(), matrixPrefix) == 0)
        {
            arg = arg.substr(matrixPrefix.size());
            matrixFile = arg.c_str();
        }
        else
        {
            names.push_back(arg);
        }
    }

    if (mode == Modes::Unset)
    {
        if (names.size() > 3)
        {
            mode = Modes::Tournament;
        }
        else if (names.size() == 3)
        {
            mode = Modes::Detailed;
        }
        else
        {
            throw "Provide at least three strategies";
        }
    }
    else if (mode == Modes::Tournament && names.size() <= 3)
    {
        throw "Not enough strategies for tournament";
    }
    else if ((mode == Modes::Detailed || mode == Modes::Fast) && names.size() != 3)
    {
        throw "Not enough strategies for tournament";
    }
}
