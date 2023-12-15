#include "PlayerNode.h"
#include "Player.h"
#include <QPainter>
#include "utils.h"
#include <iostream>

PlayerNode::PlayerNode(Player * player)
    :QGraphicsItem(),
    m_playerNode(player)
{
}

QRectF PlayerNode::boundingRect() const
{
    double canvasDiameter = Utils::getCanvasDiameter(m_playerNode->diameter());
    return QRectF(0, 0, canvasDiameter , canvasDiameter);
}

void PlayerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::darkYellow);
    // Set the pen for the circle outline
    painter->setPen(Qt::black);

    QPointF canvasPoint = Utils::setCanvasCoordiante(m_playerNode->coordinate());
    double canvasDiameter = Utils::getCanvasDiameter(m_playerNode->diameter());

    double topLeftX = canvasPoint.x() - canvasDiameter/2;
    double topLeftY = canvasPoint.y() - canvasDiameter/2;
    painter->drawEllipse(topLeftX, topLeftY, canvasDiameter, canvasDiameter);
}

