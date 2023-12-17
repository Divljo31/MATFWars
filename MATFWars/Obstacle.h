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


private:
    double m_diameter;
    double m_minSize = 2.0;
    QPointF m_center;


};

#endif // OBSTACLE_H
