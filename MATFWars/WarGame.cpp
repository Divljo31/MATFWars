#include "WarGame.h"

WarGame::WarGame()
{

}

PlayerWar WarGame::player1() const
{
    return m_player1;
}

PlayerWar WarGame::player2() const
{
    return m_player2;
}

Obstacle WarGame::getObstacle(size_t index) const
{
    return m_obstacles.at(index);
}


Canvas WarGame::canvas() const
{
    return m_canvas;
}

