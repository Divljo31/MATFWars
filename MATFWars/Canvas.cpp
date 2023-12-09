#include "Canvas.h"
#include "Function.h"
#include "FunctionNode.h"

Canvas::Canvas(QObject *parent)
    :QGraphicsScene(parent),
    m_functionNode(nullptr)
{

}

void Canvas::setFunction(FunctionNode *node)
{
    // kad prvi put postavimo funkciju onda dodamo
    if (m_functionNode == nullptr) {
        QLineF xAxis(0, this->height()/2, this->width(), this->height()/2);
        QLineF yAxis(this->width() / 2, 0, this->width() / 2, this->height());
        this->addItem(new QGraphicsLineItem(xAxis));
        this->addItem(new QGraphicsLineItem(yAxis));
    }

    if (m_functionNode != nullptr) {
        this->removeItem(m_functionNode);
        delete m_functionNode;
    }

    m_functionNode = node;

    this->addItem(m_functionNode);

}

void Canvas::centerFunctionInCanvas()
{
    //m_functionNode->setPos(this->width()/2, this->height()/2);
}
