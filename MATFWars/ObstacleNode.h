#ifndef OBSTACLENODE_H
#define OBSTACLENODE_H

#include <QGraphicsItem>
#include "Obstacle.h"

class Obstacle;

class ObstacleNode : public QGraphicsItem
{
public:
    ObstacleNode(Obstacle* obstacle);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline const Obstacle *getObstacle() {
        return m_obstacleNode;
    }



    void setCanvasDiameter(double newCanvasDiameter);

private:
    Obstacle * m_obstacleNode;
    double m_canvasDiameter;
};

#endif // OBSTACLENODE_H
