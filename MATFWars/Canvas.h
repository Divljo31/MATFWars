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
    const double m_gridWidth = 30;

    QPointF translateCoordinates(int logicalX, int logicalY);
    void addPoint(int logicalX, int logicalY);


};

#endif // CANVAS_H
