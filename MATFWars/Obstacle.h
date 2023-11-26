#ifndef OBSTACLE_H
#define OBSTACLE_H

//TODO: id, location, diameter
#include <QPointF>

class Obstacle
{
public:
    Obstacle();

    QPointF coordinates() const;
    void setCoordinates(QPointF newCoordinates);

private:
    int m_id;
    QPointF m_coordinates;
};

#endif // OBSTACLE_H
