#include "Obstacle.h"

Obstacle::Obstacle()
{
    m_maxHealth = 1 + QRandomGenerator::global()->bounded(5);
    m_health = m_maxHealth;
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

void Obstacle::flipX(){
    m_center.setX(-m_center.x());
}

void Obstacle::gotHit()
{
    m_health--;
}

bool Obstacle::isAlive()
{
    return m_health > 0;
}

double Obstacle::health() const
{
    return m_health;
}

double Obstacle::maxHealth() const
{
    return m_maxHealth;
}

double Obstacle::generateDiameter()
{

    double diameter = QRandomGenerator::global()->generateDouble();
    int scale = 1 + QRandomGenerator::global()->bounded(10);
    // 1.5 je minSize
    diameter = m_minSize + diameter * scale;

    return diameter;
}



