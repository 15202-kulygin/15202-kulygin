//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_BAD_H
#define PRISONERS_BAD_H


#include "../Strategy.h"

class Loyal : public Strategy
{
public:
    virtual ~Loyal() override;

    virtual Decision Decide() override;

    virtual void PrintData(std::ostream & stream) const override;
};


#endif //PRISONERS_BAD_H
