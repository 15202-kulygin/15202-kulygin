//
// Created by glavak on 28.10.16.
//

#include "Psycologist.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Psycologist();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("psycologist", create);
}

Psycologist::~Psycologist()
{

}

Decision Psycologist::Decide()
{
    Decision decision = Decision ::Defect;

    this->ownChoices.push_back(decision);
    return decision;
}

void Psycologist::AddEnemyDecision(Decision d1, Decision d2)
{
    choices1.push_back(d1);
    choices2.push_back(d2);
}

void Psycologist::PrintData(std::ostream & stream) const
{
    stream << "Psycologist";
}

Psycologist::StrategyType
Psycologist::guessStrategyType(std::vector<Decision> hisChoices,
                               std::vector<Decision> otherChoices1,
                               std::vector<Decision> otherChoices2)
{

}
