#include "join.h"
#include "ui_join.h"

Join::Join(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Join)
{
    ui->setupUi(this);
    ptrWaitingRoom=new WaitingRoom();

    //menjam
    ui->back_pop2_button->installEventFilter(this);
    ui->join_pop2_button->installEventFilter(this);


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

//menjam
bool Join::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->join_pop2_button && event->type()==QEvent::Enter){
        ui->join_pop2_button->setCursor(Qt::PointingHandCursor);
    }
    else if(obj==ui->back_pop2_button && event->type()==QEvent::Enter){
        ui->back_pop2_button->setCursor(Qt::PointingHandCursor);
    }

    return QDialog::eventFilter(obj,event);
}

