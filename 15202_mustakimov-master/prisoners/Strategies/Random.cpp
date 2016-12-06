//
// Created by glavak on 16.10.16.
//

#include <fstream>
#include "Random.h"
#include "../Factory.h"

namespace
{
    Strategy * create()
    {
        return new Random();
    }

    bool registered = Factory<Strategy, std::string>::getInstance()->reg("random", create);
}

Random::~Random()
{

}

Decision Random::Decide()
{
    float diceRoll = (float) rand() / (float) RAND_MAX;
    if (diceRoll < cooperateChance)
    {
        return Decision::Cooperate;
    }
    else
    {
        return Decision::Defect;
    }
}

void Random::LoadConfig(const std::string & path)
{
    static int strategyIndex = 0;

    std::ifstream file;
    file.open(path +
              "/random-" +
              std::to_string(++strategyIndex) +
              ".txt");

    file >> this->cooperateChance;
}

void Random::PrintData(std::ostream & stream) const
{
    stream << "Random(" << cooperateChance << ")";
}
