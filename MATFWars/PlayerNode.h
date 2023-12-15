#ifndef PLAYERNODE_H
#define PLAYERNODE_H

#include <QGraphicsItem>

class Player;

class PlayerNode : public QGraphicsItem
{
public:
    PlayerNode(Player *player, double canvasWidth, double canvasLength);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline const Player *getPlayer() {
        return m_player;
    }

private:
    void setCanvasCoords();

private:
    Player * m_player;
    double m_diameter = 25;
    double xCanvas;
    double yCanvas;


};

#endif // PLAYERNODE_H
