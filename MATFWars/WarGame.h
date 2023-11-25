#ifndef WARGAME_H
#define WARGAME_H

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
};

#endif // WARGAME_H
