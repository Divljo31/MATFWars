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


QVector<Obstacle> WarGame::generateObstacles(int x, int y)
{
    int numOfObstacles = QRandomGenerator::global()->bounded(8);

    QVector<Obstacle> obstacleArray(numOfObstacles);

    for(Obstacle obstacle : obstacleArray){

        obstacle.setCenter(randomPoint(x, y));
        float newDiameter = obstacle.generateDiameter(numOfObstacles);
        obstacle.setDiameter(newDiameter);

    }

    return obstacleArray;
}

QPointF WarGame::randomPoint(int x, int y)
{
    float xCoord = QRandomGenerator::global()->generateDouble();
    xCoord = (-x) + xCoord * 2.0*x;
    float yCoord = QRandomGenerator::global()->generateDouble();
    yCoord = (-y) + yCoord * 2.0*y;

    QPointF pointF(xCoord, yCoord);

    return pointF;

}
