#include "WarGame.h"

WarGame* WarGame::activeGame = nullptr;
bool WarGame::bothConnected = false;

WarGame::WarGame(QString address)
    :m_client()
{
    m_client->connect(adress);
    WarGame::activeGame = this;
}

WarGame::~WarGame(){
    delete m_client;
}

