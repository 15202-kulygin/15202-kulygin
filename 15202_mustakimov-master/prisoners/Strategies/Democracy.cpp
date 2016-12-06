//
// Created by glavak on 20.10.16.
//

#include <fstream>
#include "Democracy.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Democracy();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("democracy", create);
}

Democracy::~Democracy()
{

}

Decision Democracy::Decide()
{
    int votesForCooperate = 0;
    int votesForDefect = 0;

    for (Strategy * strategy : voters)
    {
        Decision decision = strategy->Decide();
        if (decision == Decision::Defect)
        {
            votesForDefect++;
        }
        else
        {
            votesForCooperate++;
        }
    }

    if (votesForCooperate > votesForDefect)
    {
        return Decision::Cooperate;
    }
    else if (votesForDefect > votesForCooperate)
    {
        return Decision::Defect;
    }
    else
    {
        if (rand() % 2)
        {
            return Defect;
        }
        else
        {
            return Cooperate;
        }
    }
}

void Democracy::AddEnemyDecision(Decision d1, Decision d2)
{
    for (Strategy * strategy : voters)
    {
        strategy->AddEnemyDecision(d1, d2);
    }
}


void Democracy::LoadConfig(const std::string & path)
{
// ????????
    static int strategyIndex = 0;

    std::ifstream file;
    file.open(path +
              "/democracy-" +
              std::to_string(++strategyIndex) +
              ".txt");

    std::string strategyName;

    while (!file.eof())
    {
        file >> strategyName;
        Strategy * strategy = Factory<Strategy, std::string>::getInstance()->create(strategyName);
        strategy->LoadConfig(path);
        voters.push_back(strategy);
    }
}

void Democracy::PrintData(std::ostream & stream) const
{
    stream << "Democracy(";
    for (Strategy * strategy : voters)
    {
        stream << *strategy;
        if (strategy != voters.back()) stream << ", ";
    }
    stream << ")";
}