#include "PlayerGuess.h"

PlayerGuess::PlayerGuess(QString name) : Player(name)
{

}

void PlayerGuess::setScore(int newScore)
{
    m_score = newScore;
}

int PlayerGuess::score() const
{
    return m_score;
}
