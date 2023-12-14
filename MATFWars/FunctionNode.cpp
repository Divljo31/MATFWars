#include "FunctionNode.h"
#include "Function.h"
#include <iostream>
#include <QPainter>
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

    painter->setPen(Qt::black);
    painter->drawPolyline(m_functionNode->points());

}
