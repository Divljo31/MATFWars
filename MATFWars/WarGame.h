#ifndef WARGAME_H
#define WARGAME_H

#include <QVector>
#include "PlayerWar.h"
#include "Obstacle.h"
#include "Canvas.h"
//TODO: WarPlayer[], Obstacle[], startGame, addPlayer, removePlayer, endGame

class WarGame
{
public:

    WarGame();
    static bool bothConnected;
    static bool startGame();
    static bool addPlayer();
    static bool removePlayer();
    static bool endGame();

    QVector<Obstacle> generateObstacles(int x, int y);
    QPointF randomPoint(int x, int y);


    PlayerWar player1() const;

    PlayerWar player2() const;

    Obstacle getObstacle(size_t index) const;

    Canvas canvas() const;

private:
    PlayerWar m_player1;
    PlayerWar m_player2;
    Canvas m_canvas;
    QVector<Obstacle> m_obstacles;
};

#endif // WARGAME_H
