//
// Created by glavak on 16.10.16.
//

#include "Loyal.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Loyal();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("loyal", create);
}

Loyal::~Loyal()
{

}

Decision Loyal::Decide()
{
    return Decision::Cooperate;
}

void Loyal::PrintData(std::ostream & stream) const
{
    stream << "Loyal";
}
