//
// Created by glavak on 16.10.16.
//

#include "Adaptive.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Adaptive();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("adaptive", create);
}

Adaptive::~Adaptive()
{

}

Decision Adaptive::Decide()
{
    if (move_number <= 5)
    {
        return Decision::Cooperate;
    }
    else if (move_number <= 10)
    {
        return Decision::Defect;
    }
    else
    {
        int summ = 0;
        for (Decision d : choices)
        {
            if (d == Decision::Defect) summ--;
            if (d == Decision::Cooperate) summ++;
        }
        if (summ >= 0) return Decision::Cooperate;
        else return Decision::Defect;
    }
}

void Adaptive::AddEnemyDecision(Decision d1, Decision d2)
{
    choices.push_back(d1);
    choices.push_back(d2);
}

void Adaptive::PrintData(std::ostream & stream) const
{
    stream << "Adaptive";
}
