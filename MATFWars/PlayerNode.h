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

private:
    Player * m_playerNode;
};

#endif // PLAYERNODE_H
