#include "Obstacle.h"

Obstacle::Obstacle()
{

}

void Obstacle::setXCoordinate(int newXCoordinate)
{
    m_xCoordinate = newXCoordinate;
}

int Obstacle::xCoordinate() const
{
    return m_xCoordinate;
}

int Obstacle::yCoordinate() const
{
    return m_yCoordinate;
}

void Obstacle::setYCoordinate(int newYCoordinate)
{
    m_yCoordinate = newYCoordinate;
}


