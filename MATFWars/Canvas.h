#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include "FunctionNode.h"
#include "ObstacleNode.h"
#include "PlayerNode.h"

class Function;
class FunctionNode;
class Obstacle;
class ObstacleNode;
class Player;
class PlayerNode;

class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QObject *parent = nullptr);
    double gridWidth() const;

public slots:
    void setFunction(FunctionNode *function);
    void addObstacle(ObstacleNode* obstacleNode);
    void addPlayer(PlayerNode* playerNode);
    void addCoordinateSystem();

private:
    FunctionNode * m_functionNode;
    QVector<PlayerNode*> m_playerNodes;
    QVector<ObstacleNode*> m_obstacleNodes;

    QGraphicsLineItem* xAxisItem = nullptr;
    QGraphicsLineItem* yAxisItem = nullptr;
    QVector<QGraphicsEllipseItem*> axisPoints;
    const double m_gridWidth = 30;

    QPointF getCanvasCoords(double logicalX, double logicalY);
    double scaleToCanvas(double len);
    void addPoint(int logicalX, int logicalY);


};

#endif // CANVAS_H
