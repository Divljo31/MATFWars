#ifndef OBSTACLE_H
#define OBSTACLE_H

//TODO: id, location, diameter
#include <QPointF>
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonArray>


class Obstacle
{
public:
    Obstacle();

    QPointF center() const;
    void setCenter(QPointF newCoordinates);
    float diameter() const;
    void setDiameter(double newDiameter);
    double generateDiameter();
    void flipX();
    void gotHit();
    bool isAlive();


    double health() const;

    QJsonObject createJson();
    double maxHealth() const;

    void setHealth(double newHealth);
    void setMaxHealth(double newMaxHealth);

private:
    double m_diameter;
    double m_minSize = 2.0;
    QPointF m_center;

    double m_health;
    double m_maxHealth;
};

#endif // OBSTACLE_H
