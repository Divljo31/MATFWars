#include "ObstacleNode.h"
#include <QPainter>

ObstacleNode::ObstacleNode(Obstacle * obstacle)
    : QGraphicsItem(),
    m_obstacleNode(obstacle)
{
}

QRectF ObstacleNode::boundingRect() const
{
    return QRectF(0, 0, m_canvasDiameter, m_canvasDiameter);
}

void ObstacleNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::darkCyan);
    painter->setPen(Qt::black);

    painter->drawEllipse(0,0, m_canvasDiameter, m_canvasDiameter);
}

void ObstacleNode::setCanvasDiameter(double newCanvasDiameter)
{
    m_canvasDiameter = newCanvasDiameter;
}
