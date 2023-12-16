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

void Obstacle::setDiameter(double newDiameter)
{
    m_diameter = newDiameter;
}

double Obstacle::generateDiameter()
{

    double diameter = QRandomGenerator::global()->generateDouble();
    int scale = 1 + QRandomGenerator::global()->bounded(10);
    // 1.5 je minSize
    diameter = m_minSize + diameter * scale;

    return diameter;
}



