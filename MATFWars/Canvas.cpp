#include "Canvas.h"
#include "Function.h"
#include "FunctionNode.h"

Canvas::Canvas(QObject *parent)
    :QGraphicsScene(parent),
    m_functionNode(nullptr)
{
}

QPointF Canvas::translateCoordinates(int logicalX, int logicalY) {
    double sceneX = (this->width() / 2) + (logicalX * gridWidth());
    double sceneY = (this->height() / 2) - (logicalY * gridWidth());
    return QPointF(sceneX, sceneY);
}

// Function to add a point to the scene
void Canvas::addPoint(int logicalX, int logicalY) {
    double r = 1.2;
    QPointF scenePoint = translateCoordinates(logicalX, logicalY);
    QRectF pointRect(scenePoint.x() - r, scenePoint.y() - r,
                     r * 2, r * 2);
    QGraphicsEllipseItem* point = new QGraphicsEllipseItem(pointRect);

    this->addItem(point);
}

void Canvas::addCoordinateSystem() {
    QLineF xAxis(0, this->height()/2, this->width(), this->height()/2);
    QLineF yAxis(this->width() / 2, 0, this->width() / 2, this->height());
    this->addItem(new QGraphicsLineItem(xAxis));
    this->addItem(new QGraphicsLineItem(yAxis));

    for  (int start = -gridWidth(); start <= m_gridWidth; start++) {
        addPoint(start, 0);
        addPoint(0, start);
    }
}

void Canvas::setFunction(FunctionNode *node)
{
    if (m_functionNode != nullptr) {
        this->removeItem(m_functionNode);
        delete m_functionNode;
    }

    m_functionNode = node;

    this->addItem(m_functionNode);

}

double Canvas::gridWidth() const
{
    return m_gridWidth;
}

