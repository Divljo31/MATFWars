#ifndef OBSTACLE_H
#define OBSTACLE_H

//TODO: id, location, diameter
#include <QPointF>
#include <QRandomGenerator>


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

    double maxHealth() const;

private:
    double m_diameter;
    double m_minSize = 2.0;
    QPointF m_center;

    double m_health;
    double m_maxHealth;
};

#endif // OBSTACLE_H
