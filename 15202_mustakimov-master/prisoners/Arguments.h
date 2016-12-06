//
// Created by glavak on 20.10.16.
//

#ifndef PRISONERS_ARGUMENTS_H
#define PRISONERS_ARGUMENTS_H

#include <iostream>
#include <vector>
#include <string>

enum Modes
{
    Unset,
    Detailed,
    Fast,
    Tournament
};

class Arguments
{
public:
    std::vector<std::string> names;
    int steps = 1;
    Modes mode = Modes::Unset;
    std::string configDirectory = "configs";
    std::string matrixFile = "";

    Arguments(int argc, char * argv[]);
};


#endif //PRISONERS_ARGUMENTS_H
