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
    }
    else if(obj==ui->back_pop1_button && event->type()==QEvent::Enter){
        ui->back_pop1_button->setCursor(Qt::PointingHandCursor);
    }

    return QDialog::eventFilter(obj,event);
}
