#include "join.h"
#include "ui_join.h"

Join::Join(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Join)
{
    ui->setupUi(this);
    ptrWaitingRoom=new WaitingRoom();
}

Join::~Join()
{
    delete ui;
    delete ptrWaitingRoom;
}

void Join::on_back_pop2_button_clicked()
{
    emit backJoinPop2Clicked();
    this->hide();
}


void Join::on_join_pop2_button_clicked()
{
    ptrWaitingRoom->show();
}

