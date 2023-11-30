#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame)
{
    ui->setupUi(this);

}

WarGame::~WarGame()
{
    delete ui;

}

void WarGame::on_back_war_button_clicked()
{
    emit backWarClicked();
    this->hide();
}



