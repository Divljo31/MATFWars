#include "Canvas.h"
#include "Function.h"
#include "FunctionNode.h"

Canvas::Canvas(QObject *parent)
    :QGraphicsScene(parent)
{

}

void Canvas::setFunction(FunctionNode *node)
{
    m_functionNode = node;
    addItem(node);
}

void Canvas::postionFunctionInCanvas()
{

}
