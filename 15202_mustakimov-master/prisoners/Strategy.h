//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_STRATEGY_H
#define PRISONERS_STRATEGY_H


#include <iostream>

enum Decision
{
    Defect,
    Cooperate
};


class Strategy
{
public:
    virtual ~Strategy(){}

    virtual Decision Decide() = 0;
    virtual void AddEnemyDecision(Decision d1, Decision d2) {}
    virtual void LoadConfig(const std::string & path) {}

    virtual void PrintData(std::ostream & stream) const = 0;

    friend std::ostream & operator<<(std::ostream & os, const Strategy & strategy);
};


#endif //PRISONERS_STRATEGY_H
