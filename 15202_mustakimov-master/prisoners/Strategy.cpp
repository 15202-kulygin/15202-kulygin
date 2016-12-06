//
// Created by glavak on 16.10.16.
//

#include "Strategy.h"

std::ostream & operator<<(std::ostream & os, const Strategy & strategy)
{
    strategy.PrintData(os);
    return os;
}