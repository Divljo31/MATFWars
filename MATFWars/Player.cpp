#include "Player.h"

Player::Player(QString name)
    : m_name(name)
{

}

QString Player::name() const
{
    return m_name;
}
