#ifndef PLAYERGUESS_H
#define PLAYERGUESS_H

#include "Player.h"
// TODO: score, destruktor

class PlayerGuess: public Player
{
public:
    PlayerGuess(QString name = "player");


    void setScore(int newScore);

    int score() const;

private:
    int m_score;
};

#endif // PLAYERGUESS_H
