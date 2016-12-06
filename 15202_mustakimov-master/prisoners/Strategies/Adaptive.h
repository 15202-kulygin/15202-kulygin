//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_ADAPTIVE_H
#define PRISONERS_ADAPTIVE_H


#include "../Strategy.h"

class Adaptive : public Strategy
{
public:
    virtual ~Adaptive() override;

    virtual Decision Decide() override;
    virtual void AddEnemyDecision(Decision d1, Decision d2) override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    int move_number = 0;

    std::vector<Decision> choices;
};


#endif //PRISONERS_ADAPTIVE_H
