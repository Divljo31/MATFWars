#include "PlayerNode.h"
#include "Player.h"
#include <QPainter>
#include <iostream>

PlayerNode::PlayerNode(Player * player)
    :QGraphicsItem(),
    m_playerNode(player)
{
}

QRectF PlayerNode::boundingRect() const
{
    return QRectF(0, 0, m_canvasDiameter , m_canvasDiameter);
}

void PlayerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::darkYellow);
    painter->setPen(Qt::black);

    painter->drawEllipse(0, 0, m_canvasDiameter, m_canvasDiameter);

    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    QFontMetrics metrics(font);
    QRect textRect = metrics.boundingRect(m_playerNode->name());

    int textX = (m_canvasDiameter - textRect.width()) / 2;

    painter->drawText(textX, -3, m_playerNode->name());
}

void PlayerNode::setCanvasDiameter(double newCanvasDiameter)
{
    m_canvasDiameter = newCanvasDiameter;
}

