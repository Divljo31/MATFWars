#ifndef WARGAME_H
#define WARGAME_H

#include "PlayerWar.h"
#include "Obstacle.h"
//TODO: WarPlayer[], Obstacle[], startGame, addPlayer, removePlayer, endGame

class WarGame
{
public:

    WarGame();
    static WarGame* activeGame;
    static bool bothConnected;
    static bool startGame();
    static bool addPlayer();
    static bool removePlayer();
    static bool endGame();


private:
    PlayerWar m_player1;
    PlayerWar m_player2;
    Obstacle m_obstacles[];
};

#endif // WARGAME_H
