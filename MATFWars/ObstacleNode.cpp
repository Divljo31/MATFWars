#include "ObstacleNode.h"
#include <QPainter>
#include "utils.h"

ObstacleNode::ObstacleNode(Obstacle * obstacle)
    : QGraphicsItem(),
    m_obstacleNode(obstacle)
{
}

QRectF ObstacleNode::boundingRect() const
{
    double canvasDiameter = Utils::getCanvasDiameter(m_obstacleNode->diameter());
    return QRectF(0, 0, canvasDiameter, canvasDiameter);
}

void ObstacleNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::darkCyan);
    // Set the pen for the circle outline
    painter->setPen(Qt::black);

    QPointF canvasPoint = Utils::setCanvasCoordiante(m_obstacleNode->center());
    double canvasDiameter = Utils::getCanvasDiameter(m_obstacleNode->diameter());

    double topLeftX = canvasPoint.x() - canvasDiameter/2;
    double topLeftY = canvasPoint.y() - canvasDiameter/2;
    painter->drawEllipse(topLeftX, topLeftY, canvasDiameter, canvasDiameter);
}
