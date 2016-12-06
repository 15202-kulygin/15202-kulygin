//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_RANDOM_H
#define PRISONERS_RANDOM_H


#include "../Strategy.h"

class Random : public Strategy
{
public:
    virtual ~Random() override;

    virtual Decision Decide() override;
    virtual void LoadConfig(const std::string & path) override;

    virtual void PrintData(std::ostream & stream) const override;

private:
    float cooperateChance;
};


#endif //PRISONERS_RANDOM_H
