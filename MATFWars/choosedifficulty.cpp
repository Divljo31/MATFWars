#include "choosedifficulty.h"
#include "ui_choosedifficulty.h"

ChooseDifficulty::ChooseDifficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDifficulty)
{
    ui->setupUi(this);
    ptrGuessGame=new GuessGame();
}

ChooseDifficulty::~ChooseDifficulty()
{
    delete ui;
    delete ptrGuessGame;
}

void ChooseDifficulty::on_pushButton_clicked()
{
    ptrGuessGame->show();
    this->hide();

}
