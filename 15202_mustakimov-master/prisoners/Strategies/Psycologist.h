//
// Created by glavak on 28.10.16.
//

#ifndef PRISONERS_PSYCOLOGIST_H
#define PRISONERS_PSYCOLOGIST_H


#include <vector>
#include "../Strategy.h"

class Psycologist : public Strategy
{
public:
    virtual ~Psycologist() override;

    virtual Decision Decide() override;
    virtual void AddEnemyDecision(Decision d1, Decision d2) override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    enum StrategyType
    {
        Traitor,
        Loyal,
        Revengeful,
        Unknown
    };

    std::vector<Decision> choices1;
    std::vector<Decision> choices2;
    std::vector<Decision> ownChoices;

    StrategyType guessStrategyType(std::vector<Decision> hisChoices,
                                   std::vector<Decision> otherChoices1,
                                   std::vector<Decision> otherChoices2);
};


#endif //PRISONERS_PSYCOLOGIST_H
