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

QJsonObject Obstacle::createJson()
{
    // Add obstacles to the array
    QJsonObject obstacleObject;
    obstacleObject["m_diameter"] = m_diameter;
    obstacleObject["m_center"] = QJsonObject{
        {"x", m_center.x()},
        {"y", m_center.y()}
    };
    obstacleObject["m_health"] = m_health;
    obstacleObject["m_maxHealth"] = m_maxHealth;

    return obstacleObject;

}

double Obstacle::maxHealth() const
{
    return m_maxHealth;
}

void Obstacle::setHealth(double newHealth)
{
    m_health = newHealth;
}

void Obstacle::setMaxHealth(double newMaxHealth)
{
    m_maxHealth = newMaxHealth;
}

double Obstacle::generateDiameter()
{

    double diameter = QRandomGenerator::global()->generateDouble();
    int scale = 1 + QRandomGenerator::global()->bounded(10);
    // 1.5 je minSize
    diameter = m_minSize + diameter * scale;

    return diameter;
}



