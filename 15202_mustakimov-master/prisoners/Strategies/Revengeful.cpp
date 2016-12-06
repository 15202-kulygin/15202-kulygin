//
// Created by glavak on 16.10.16.
//

#include "Revengeful.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Revengeful();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("revengeful", create);
}

Revengeful::~Revengeful()
{

}

Decision Revengeful::Decide()
{
    if (anyoneTraitedMeLastTime)
    {
        return Defect;
    }
    else
    {
        return Cooperate;
    }
}

void Revengeful::AddEnemyDecision(Decision d1, Decision d2)
{
    this->anyoneTraitedMeLastTime =
            d1 == Decision::Defect
            || d2 == Decision::Defect;
}

void Revengeful::PrintData(std::ostream & stream) const
{
    stream << "Revengeful";
}
