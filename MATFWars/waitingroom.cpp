#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(Client *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingRoom),
    m_client(client)
{
    ui->setupUi(this);
    ptrWarGame = new WarGame(m_client);

    //menjano!!!
    connect(ptrWarGame,&WarGame::backWarClicked, this, &WaitingRoom::show);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
    delete ptrWarGame;
}

void WaitingRoom::on_play_wait_button_clicked()
{
    this->hide();
    ptrWarGame->show();
}


void WaitingRoom::on_back_wait_button_clicked()
{
    emit backWaitingRoomClicked();
    this->hide();
}

void WaitingRoom::setClient(Client *newClient)
{
    m_client = newClient;
}

