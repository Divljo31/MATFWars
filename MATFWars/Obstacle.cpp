#include "Obstacle.h"

Obstacle::Obstacle()
{

}

QPointF Obstacle::center() const
{
    return m_center;
}

void Obstacle::setCenter(QPointF newCenter)
{
    m_center = newCenter;
}

float Obstacle::diameter() const
{
    return m_diameter;
}

void Obstacle::setDiameter(float newDiameter)
{
    m_diameter = newDiameter;
}

float Obstacle::generateDiameter(int numOfObstacles)
{

    float diameter = QRandomGenerator::global()->generateDouble();
    diameter = 0.1 + diameter * (10 - numOfObstacles)/2;

    return diameter;
}



