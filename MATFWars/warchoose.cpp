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
    ui->create_choose_button->installEventFilter(this);
    ui->join_choose_button->installEventFilter(this);
    ui->back_choose_button->installEventFilter(this);

    //menjam
    connect(ptrCreate,&Create::backCreatePop1Clicked,this,&WarChoose::show);
    connect(ptrJoin,&Join::backJoinPop2Clicked,this,&WarChoose::show);

    createStyle=ui->create_choose_button->styleSheet();
    joinStyle=ui->join_choose_button->styleSheet();
    backStyle=ui->back_choose_button->styleSheet();

    ui->create_choose_button->setDefault(true);
    ui->create_choose_button->setAutoDefault(true);
    ui->join_choose_button->setDefault(false);
    ui->join_choose_button->setAutoDefault(false);
    ui->back_choose_button->setDefault(false);
    ui->back_choose_button->setAutoDefault(false);
}

WarChoose::~WarChoose()
{
    delete ui;
    if(ptrCreate != nullptr)
        delete ptrCreate;
    if(ptrJoin != nullptr)
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

//menjam
bool WarChoose::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->create_choose_button && event->type()==QEvent::Enter){
        ui->create_choose_button->setCursor(Qt::PointingHandCursor);
        ui->create_choose_button->setStyleSheet(createStyle+"border:5px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->join_choose_button && event->type()==QEvent::Enter){
        ui->join_choose_button->setCursor(Qt::PointingHandCursor);
        ui->join_choose_button->setStyleSheet(joinStyle+"border:5px solid rgb(180, 72, 72);");

    }
    else if(obj==ui->back_choose_button && event->type()==QEvent::Enter){
        ui->back_choose_button->setCursor(Qt::PointingHandCursor);
        ui->back_choose_button->setStyleSheet(backStyle+"border:5px solid rgb(180, 72, 72);");

    }
    else if(obj==ui->create_choose_button && event->type()==QEvent::Leave){
        ui->create_choose_button->setStyleSheet(createStyle);
    }
    else if(obj==ui->join_choose_button && event->type()==QEvent::Leave){
        ui->join_choose_button->setStyleSheet(joinStyle);
    }
    else if(obj==ui->back_choose_button && event->type()==QEvent::Leave){
        ui->back_choose_button->setStyleSheet(backStyle);

    }

    return QDialog::eventFilter(obj,event);
}

