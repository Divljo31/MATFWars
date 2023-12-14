#include "create.h"
#include "ui_create.h"

Create::Create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create)
{
    ui->setupUi(this);
    ptrWaitingRoom=new WaitingRoom();

    //menjam
    ui->create_pop1_button->installEventFilter(this);
    ui->back_pop1_button->installEventFilter(this);
    createStyle=ui->create_pop1_button->styleSheet();
    backStyle=ui->back_pop1_button->styleSheet();
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

//menjam
bool Create::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->create_pop1_button && event->type()==QEvent::Enter){
        ui->create_pop1_button->setCursor(Qt::PointingHandCursor);
        ui->create_pop1_button->setStyleSheet(createStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->back_pop1_button && event->type()==QEvent::Enter){
        ui->back_pop1_button->setCursor(Qt::PointingHandCursor);
        ui->back_pop1_button->setStyleSheet(backStyle+"border:4px solid rgb(180, 72, 72);");

    }
    else if(obj==ui->create_pop1_button && event->type()==QEvent::Leave){
        ui->create_pop1_button->setStyleSheet(createStyle);
    }
    else if(obj==ui->back_pop1_button && event->type()==QEvent::Leave){
        ui->back_pop1_button->setStyleSheet(backStyle);
    }

    return QDialog::eventFilter(obj,event);
}

