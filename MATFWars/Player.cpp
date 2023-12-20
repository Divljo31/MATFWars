#include "Player.h"

Player::Player(QString name)
    : m_name(name)
{

}

QString Player::name() const
{
    return m_name;
}

void Player::setName(const QString &newName)
{
    m_name = newName;
}

QPointF Player::coordinate() const
{
    return m_coordinate;
}

void Player::setCoordinates(QPointF newCoordinates)
{
    m_coordinate = newCoordinates;
}

double Player::diameter() const
{
    return m_diameter;
}

void Player::flipX()
{
    m_coordinate.setX(-m_coordinate.x());
}

QJsonObject Player::createJson()
{
    QJsonObject playerObject;
    playerObject["m_name"] = m_name;
    playerObject["m_coordinate"] = QJsonObject{
        {"x", m_coordinate.x()},
        {"y", m_coordinate.y()}
    };

    return playerObject;
}

