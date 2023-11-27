#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include <QGraphicsItem>

class Function;

class FunctionNode : public QGraphicsItem
{
public:
    FunctionNode(Function *function);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline const Function *getFunction() const
    {
        return m_functionNode;
    }

    inline qint32 width() const { return 500; }
    inline qint32 height() const { return 500; }

private:
    Function *m_functionNode;

};

#endif // FUNCTIONNODE_H
