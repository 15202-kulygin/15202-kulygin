//
// Created by glavak on 20.10.16.
//

#ifndef PRISONERS_DEMOCRACY_H
#define PRISONERS_DEMOCRACY_H


#include <vector>
#include "../Strategy.h"

class Democracy : public Strategy
{
public:
    virtual ~Democracy() override;

    virtual Decision Decide() override;
    virtual void AddEnemyDecision(Decision d1, Decision d2) override;
    virtual void LoadConfig(const std::string & path) override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    std::vector<Strategy *> voters;
};


#endif //PRISONERS_DEMOCRACY_H
