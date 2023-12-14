#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include <QGraphicsItem>

class Function;

class FunctionNode : public QGraphicsItem
{
public:
    FunctionNode(Function *function, double width, double height);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline const Function *getFunction()
    {
        return m_functionNode;
    }

private:
    Function *m_functionNode;
    QRectF m_boundingRect;
};

#endif // FUNCTIONNODE_H
