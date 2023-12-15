#include "PlayerWar.h"

PlayerWar::PlayerWar(QString name)
{

}

QPointF PlayerWar::coordinates() const
{
    return m_coordinates;
}

void PlayerWar::setCoordinates(QPointF newCoordinates)
{
    m_coordinates = newCoordinates;
}




