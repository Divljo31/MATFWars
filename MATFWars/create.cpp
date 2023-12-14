#include "create.h"
#include "ui_create.h"

Create::Create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create)
{
    ui->setupUi(this);
    ptrWaitingRoom=new WaitingRoom();

    connect(ptrWaitingRoom,&WaitingRoom::backWaitingRoomClicked,this,&Create::show);

}

Create::~Create()
{
    delete ui;
    delete ptrWaitingRoom;
}

void Create::on_back_pop1_button_clicked()
{
    //menjam
    emit backCreatePop1Clicked();
    this->hide();
}


void Create::on_create_pop1_button_clicked()
{
    this->hide();
    ptrWaitingRoom->show();
}




