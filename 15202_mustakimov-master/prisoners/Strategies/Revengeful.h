//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_REVENGEFUL_H
#define PRISONERS_REVENGEFUL_H


#include "../Strategy.h"

class Revengeful : public Strategy
{
public:
    virtual ~Revengeful() override;

    virtual Decision Decide() override;
    virtual void AddEnemyDecision(Decision d1, Decision d2) override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    bool anyoneTraitedMeLastTime = false;
};


#endif //PRISONERS_REVENGEFUL_H
