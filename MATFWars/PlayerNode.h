#ifndef PLAYERNODE_H
#define PLAYERNODE_H

#include <QGraphicsItem>

class Player;

class PlayerNode : public QGraphicsItem
{
public:
    PlayerNode(Player *player);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline const Player *getPlayer() {
        return m_playerNode;
    }

    void setCanvasDiameter(double newCanvasDiameter);

private:
    Player * m_playerNode;
    double m_canvasDiameter = 100;
};

#endif // PLAYERNODE_H
