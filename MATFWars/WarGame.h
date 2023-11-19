#ifndef WARGAME_H
#define WARGAME_H

//TODO: WarPlayer[], Obstacle[], startGame, addPlayer, removePlayer, endGame

class WarGame
{
public:
    WarGame(QString address);
    static WarGame* activeGame;
    static bool bothConnected;
    startGame();
    addPlayer();
    removePlayer();
    endGame();
private:
};

#endif // WARGAME_H
