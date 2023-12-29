#include "FunctionNode.h"
#include "Function.h"
#include <iostream>
#include <QPainter>

#include "settings.h"

using namespace std;
FunctionNode::FunctionNode(Function *function, double width, double height)
    : QGraphicsItem()
    , m_functionNode(function)
{
    m_boundingRect = QRectF(0, 0, width, height);
}

QRectF FunctionNode::boundingRect() const
{
    return m_boundingRect;
}

void FunctionNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor currentColor = Settings::funcColor;
    QPen pen;
    pen.setColor(currentColor);
    pen.setWidth(2);

    painter->setPen(pen);
    painter->drawPolyline(m_functionNode->points());
}
