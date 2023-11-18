#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

// TODO: Nakon implementacije klase Funkcija.cpp potrebno je dodati klasi Player polje: Function lastUsedFunction.

class Player {
public:
    Player(QString name = "player");
    QString name() const;

private:
    QString m_name;
};

#endif // PLAYER_H
