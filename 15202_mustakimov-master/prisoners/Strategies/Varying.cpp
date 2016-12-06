//
// Created by glavak on 19.10.16.
//

#include "Varying.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Varying();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("varying", create);
}

Varying::~Varying()
{

}

Decision Varying::Decide()
{
    if (this->lastDecision == Decision::Cooperate)
    {
        return this->lastDecision = Decision::Defect;
    }
    else
    {
        return this->lastDecision = Decision::Cooperate;
    }
}


void Varying::PrintData(std::ostream & stream) const
{
    stream << "Varying";
}
