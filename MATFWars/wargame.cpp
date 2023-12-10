#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame)
{
    ui->setupUi(this);
    ptrCheck=new Check();

    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);

}

WarGame::~WarGame()
{
    delete ui;
    delete ptrCheck;

}

void WarGame::on_back_war_button_clicked()
{
    emit backWarClicked();
    this->hide();
}




void WarGame::on_quit_war_button_clicked()
{
    ptrCheck->show();
}

