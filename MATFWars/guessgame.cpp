#include "guessgame.h"
#include "ui_guessgame.h"

GuessGame::GuessGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuessGame)
{
    ui->setupUi(this);
}

GuessGame::~GuessGame()
{
    delete ui;
}
