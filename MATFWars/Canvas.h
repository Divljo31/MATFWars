#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>

class Function;
class FunctionNode;

class Canvas : public QGraphicsScene
{
public:
    explicit Canvas(QObject *parent = nullptr);

public slots:
    void setFunction(FunctionNode *function);

private:
    void postionFunctionInCanvas();

    FunctionNode * m_functionNode;

};

#endif // CANVAS_H
