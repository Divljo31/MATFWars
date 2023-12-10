#include "warchoose.h"
#include "ui_warchoose.h"

WarChoose::WarChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarChoose)
{
    ui->setupUi(this);
    ptrCreate=new Create();
    ptrJoin=new Join();

    //menjam
    connect(ptrCreate,&Create::backCreatePop1Clicked,this,&WarChoose::show);
    connect(ptrJoin,&Join::backJoinPop2Clicked,this,&WarChoose::show);
}

WarChoose::~WarChoose()
{
    delete ui;
    delete ptrCreate;
    delete ptrJoin;
}

void WarChoose::on_create_choose_button_clicked()
{
    //menjam
    this->hide();
    ptrCreate->show();
}


void WarChoose::on_join_choose_button_clicked()
{
    this->hide();
    ptrJoin->show();

}



// menjano
void WarChoose::on_back_choose_button_clicked()
{
    emit backChooseClicked();
    this->hide();
}

