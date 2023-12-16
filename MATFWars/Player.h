#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QPointF>
// TODO: Nakon implementacije klase Funkcija.cpp potrebno je dodati klasi Player polje: Function lastUsedFunction.

class Player {
public:
    Player(QString name = "player");
    virtual QString name() const;

    virtual void setName(const QString &newName);

    QPointF coordinate() const;

    void setCoordinates(QPointF newCoordinates);

    double diameter() const;

private:
    QString m_name;
    QPointF m_coordinate;
    double m_diameter = 1.0;
};

#endif // PLAYER_H
