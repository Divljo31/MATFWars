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
