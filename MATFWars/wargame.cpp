#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame)
{
    ui->setupUi(this);
    ptrCheck=new Check();

    //menjam
    ui->fire_war_button->installEventFilter(this);
    ui->quit_war_button->installEventFilter(this);
    ui->back_war_button->installEventFilter(this);

    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);

    backStyle=ui->back_war_button->styleSheet();
    quitStyle=ui->quit_war_button->styleSheet();
    fireStyle=ui->fire_war_button->styleSheet();
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

//menjam
bool WarGame::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->fire_war_button && event->type()==QEvent::Enter){
        ui->fire_war_button->setCursor(Qt::PointingHandCursor);
        ui->fire_war_button->setStyleSheet(fireStyle+"border: 7px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->quit_war_button && event->type()==QEvent::Enter){
        ui->quit_war_button->setCursor(Qt::PointingHandCursor);
        ui->quit_war_button->setStyleSheet(quitStyle+"border: 7px solid rgb(180, 72, 72);");

    }
    else if(obj==ui->back_war_button && event->type()==QEvent::Enter){
        ui->back_war_button->setCursor(Qt::PointingHandCursor);
        ui->back_war_button->setStyleSheet(backStyle+"border: 7px solid rgb(180, 72, 72);");

    }
    else if(obj==ui->fire_war_button && event->type()==QEvent::Leave){
        ui->fire_war_button->setStyleSheet(fireStyle);
    }
    else if(obj==ui->quit_war_button && event->type()==QEvent::Leave){
        ui->quit_war_button->setStyleSheet(quitStyle);
    }
    else if(obj==ui->back_war_button && event->type()==QEvent::Leave){
        ui->back_war_button->setStyleSheet(backStyle);

    }

    return QDialog::eventFilter(obj,event);
}
