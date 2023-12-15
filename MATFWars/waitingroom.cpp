#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingRoom)
{
    ui->setupUi(this);
    ptrWarGame=new WarGame();

    //menjam
    ui->back_wait_button->installEventFilter(this);
    ui->play_wait_button->installEventFilter(this);

    //menjano!!!
    connect(ptrWarGame,&WarGame::backWarClicked, this, &WaitingRoom::show);

    backStyle=ui->back_wait_button->styleSheet();
    playStyle=ui->play_wait_button->styleSheet();
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
    delete ptrWarGame;
}

void WaitingRoom::on_play_wait_button_clicked()
{
    this->hide();
    ptrWarGame->show();
}


void WaitingRoom::on_back_wait_button_clicked()
{
    emit backWaitingRoomClicked();
    this->hide();
}

//menjam
bool WaitingRoom::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->back_wait_button && event->type()==QEvent::Enter){
        ui->back_wait_button->setCursor(Qt::PointingHandCursor);
        ui->back_wait_button->setStyleSheet(backStyle+"border:10px solid;");
    }
    else if(obj==ui->play_wait_button && event->type()==QEvent::Enter){
        ui->play_wait_button->setCursor(Qt::PointingHandCursor);
        ui->play_wait_button->setStyleSheet(playStyle+"border:10px solid;");
    }
    else if(obj==ui->back_wait_button && event->type()==QEvent::Leave){
        ui->back_wait_button->setStyleSheet(backStyle);
    }
    else if(obj==ui->play_wait_button && event->type()==QEvent::Leave){
        ui->play_wait_button->setStyleSheet(playStyle);
    }

    return QDialog::eventFilter(obj,event);
}
