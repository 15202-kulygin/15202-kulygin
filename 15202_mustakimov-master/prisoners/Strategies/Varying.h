//
// Created by glavak on 19.10.16.
//

#ifndef PRISONERS_VARYING_H
#define PRISONERS_VARYING_H


#include "../Strategy.h"

class Varying : public Strategy
{
public:
    virtual ~Varying() override;

    virtual Decision Decide() override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    Decision lastDecision = Decision::Defect;
};


#endif //PRISONERS_VARYING_H
