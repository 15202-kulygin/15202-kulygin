//
// Created by glavak on 16.10.16.
//

#include <fstream>
#include "ScoreMatrix.h"

ScoreMatrix::ScoreMatrix()
{
    defectsScores = new int[4]{-1/*doesn't matter*/, 0, 2, 4};
    cooperatesScores = new int[4]{1, 3, 5, -1/*doesn't matter*/};
}

int * ScoreMatrix::getScores(Decision d1, Decision d2, Decision d3)
{
    int cooperateCount = 0;

    if (d1 == Decision::Cooperate) cooperateCount++;
    if (d2 == Decision::Cooperate) cooperateCount++;
    if (d3 == Decision::Cooperate) cooperateCount++;

    int * scores = new int[3];

    if (d1 == Decision::Cooperate)
    {
        scores[0] = defectsScores[cooperateCount];
    }
    else
    {
        scores[0] = cooperatesScores[cooperateCount];
    }

    if (d2 == Decision::Cooperate)
    {
        scores[1] = defectsScores[cooperateCount];
    }
    else
    {
        scores[1] = cooperatesScores[cooperateCount];
    }

    if (d3 == Decision::Cooperate)
    {
        scores[2] = defectsScores[cooperateCount];
    }
    else
    {
        scores[2] = cooperatesScores[cooperateCount];
    }

    return scores;
}

void ScoreMatrix::loadFromFile(const std::string & filename)
{
    std::ifstream file;
    file.open(filename);
    std::string ignore;

    file >> ignore;
    file >> defectsScores[1];
    file >> defectsScores[2];
    file >> defectsScores[3];

    file >> cooperatesScores[0];
    file >> cooperatesScores[1];
    file >> cooperatesScores[2];
    file >> ignore;
}
