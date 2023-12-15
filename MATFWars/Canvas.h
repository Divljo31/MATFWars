#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>

class Function;
class FunctionNode;

class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QObject *parent = nullptr);
    double gridWidth() const;


public slots:
    void setFunction(FunctionNode *function);
    void addCoordinateSystem();

private:
    FunctionNode * m_functionNode;
    QGraphicsLineItem* xAxisItem = nullptr;
    QGraphicsLineItem* yAxisItem = nullptr;
    QVector<QGraphicsEllipseItem*> axisPoints;
    const double m_gridWidth = 30;

    void translateCoordinates(QPointF* point);
    void addPoint(int logicalX, int logicalY);


};

#endif // CANVAS_H
