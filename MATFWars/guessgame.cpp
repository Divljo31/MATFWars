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

void GuessGame::on_back_guess_button_clicked()
{
    emit backGuessClicked();
    this->hide();
}

