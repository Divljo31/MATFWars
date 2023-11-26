#include "Obstacle.h"

Obstacle::Obstacle()
{

}

QPointF Obstacle::coordinates() const
{
    return m_coordinates;
}

void Obstacle::setCoordinates(QPointF newCoordinates)
{
    m_coordinates = newCoordinates;
}

int Obstacle::diameter() const
{
    return m_diameter;
}

void Obstacle::setDiameter(int newDiameter)
{
    m_diameter = newDiameter;
}


