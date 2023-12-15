#include "PlayerNode.h"
#include <QPainter>

PlayerNode::PlayerNode(Player * player)
    :QGraphicsItem(),
    m_player(player)
{
}

QRectF PlayerNode::boundingRect() const
{
    return QRectF(0, 0, m_diameter, m_diameter);
}

void PlayerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::darkYellow);

    // Set the pen for the circle outline
    painter->setPen(Qt::black);

    // Draw the circle
    painter->drawEllipse(100, 100, m_diameter, m_diameter);
}

void PlayerNode::setCanvasCoords()
{

}
