//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_CONTROLLER_H
#define PRISONERS_CONTROLLER_H


#include <unordered_map>
#include <vector>
#include "Strategy.h"
#include "ScoreMatrix.h"


// ???????
struct StrategyInfo
{
    StrategyInfo(Strategy * strategy)
    {
        this->strategy = strategy;
    }

    Strategy * strategy;
    int currentScore = 0;
    int lastScore = 0;
    Decision lastDecision;
};

class Controller
{
public:
    Controller(
            const ScoreMatrix & matrix,
            const std::string & strategiesConfigPath,
            const std::vector<std::string> & names,
            int steps);
    virtual void doJob() = 0;

    void printState() const;
    void printWinner() const;

protected:
    int steps;

    void fight(size_t num1, size_t num2, size_t num3);

    std::vector<StrategyInfo> strategies;
private:
    ScoreMatrix scoreMatrix;
    std::string strategiesConfigPath;

    void addStrategy(const std::string & name);

};


#endif //PRISONERS_CONTROLLER_H
