#ifndef PLAYERWAR_H
#define PLAYERWAR_H

#include "Player.h"

class PlayerWar: public Player
{
public:
    PlayerWar(QString name = "player");

    void setXCoordinate(int newXCoordinate);

    void setYCoordinate(int newYCoordinate);


private:
    int m_xCoordinate;
    int m_yCoordinate;
};

#endif // PLAYERWAR_H
