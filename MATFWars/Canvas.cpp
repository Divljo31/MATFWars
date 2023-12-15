#include "Canvas.h"
#include "FunctionNode.h"

Canvas::Canvas(QObject *parent)
    :QGraphicsScene(parent),
    m_functionNode(nullptr)
{
}

void Canvas::translateCoordinates(QPointF * point) {
    double sceneX = point->x()*this->width()/gridWidth();
    sceneX += this->width()/2;
    point->setX(sceneX);

    double sceneY = -point->y()*this->width()/gridWidth();
    sceneY += this->height()/2;
    point->setY(sceneY);
}

// Function to add a point to the scene
void Canvas::addPoint(int logicalX, int logicalY) {
    double r = 1.5;
    QPointF scenePoint(logicalX, logicalY);
    translateCoordinates(&scenePoint);

    QRectF pointRect(scenePoint.x() - r, scenePoint.y() - r,
                     r * 2, r * 2);
    QGraphicsEllipseItem* point = new QGraphicsEllipseItem(pointRect);

    axisPoints.push_back(point);
}

void Canvas::addCoordinateSystem() {
    QLineF xAxis(0, this->height()/2, this->width(), this->height()/2);
    QLineF yAxis(this->width() / 2, 0, this->width() / 2, this->height());

    if (xAxisItem != nullptr) {
        this->removeItem(xAxisItem);
        delete xAxisItem;
    }

    if (yAxisItem != nullptr) {
        this->removeItem(yAxisItem);
        delete yAxisItem;
    }

    xAxisItem = new QGraphicsLineItem(xAxis);
    yAxisItem = new QGraphicsLineItem(yAxis);

    this->addItem(xAxisItem);
    this->addItem(yAxisItem);

    while (!axisPoints.empty()) {
        QGraphicsEllipseItem* point = axisPoints.back();
        axisPoints.pop_back();
        this->removeItem(point);
        delete point;
    }

    for  (int start = -gridWidth(); start <= gridWidth(); start++) {
        addPoint(start, 0);
        addPoint(0, start);
    }

    for (QGraphicsEllipseItem* point : axisPoints) {
        this->addItem(point);
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

