//
// Created by glavak on 16.10.16.
//

#ifndef PRISONERS_SCOREMATRIX_H
#define PRISONERS_SCOREMATRIX_H

#include "Strategy.h"

class ScoreMatrix
{
public:
    ScoreMatrix();
    int * getScores(Decision d1, Decision d2, Decision d3);
    void loadFromFile(const std::string & filename);


private:
    int * defectsScores;
    int * cooperatesScores;
};


#endif //PRISONERS_SCOREMATRIX_H
