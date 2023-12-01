#ifndef PLAYERWAR_H
#define PLAYERWAR_H

#include "Player.h"
#include <QPointF>

class PlayerWar: public Player
{
public:
    PlayerWar(QString name = "player");

    QPointF coordinates() const;

    void setCoordinates(QPointF newCoordinates);


private:
    QPointF m_coordinates;
};

#endif // PLAYERWAR_H
