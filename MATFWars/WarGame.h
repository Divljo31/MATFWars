#ifndef WARGAME_H
#define WARGAME_H

#include <vector>
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


    PlayerWar player1() const;

    PlayerWar player2() const;

    Obstacle getObstacle(size_t index) const;

    WarGame getActiveGame() const;

    Canvas canvas() const;

    int gameId() const;

private:
    PlayerWar m_player1;
    PlayerWar m_player2;
    Canvas m_canvas;
    std::vector<Obstacle> m_obstacles;
};

#endif // WARGAME_H
