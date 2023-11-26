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
    void setDiameter(float newDiameter);

    float generateDiameter(int numOfObstacles);


private:
    float m_diameter;
    QPointF m_center;


};

#endif // OBSTACLE_H
