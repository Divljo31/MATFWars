#include "join.h"
#include "ui_join.h"

Join::Join(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Join)
{


    ui->setupUi(this);
    ui->ip_lineEdit->setText("localhost");

    //menjam
    ui->back_pop2_button->installEventFilter(this);
    ui->join_pop2_button->installEventFilter(this);

    backStyle=ui->back_pop2_button->styleSheet();
    joinStyle=ui->join_pop2_button->styleSheet();

    ui->join_pop2_button->setDefault(false);
    ui->join_pop2_button->setAutoDefault(false);
    ui->back_pop2_button->setDefault(false);
    ui->back_pop2_button->setAutoDefault(false);
    ui->name_lineEdit->setFocusPolicy(Qt::StrongFocus);
}

Join::~Join()
{
    delete ui;
    if(ptrWarGame != nullptr)
        delete ptrWarGame;
}

void Join::on_back_pop2_button_clicked()
{
    emit backJoinPop2Clicked();
    this->hide();
}


void Join::on_join_pop2_button_clicked()
{
    m_client = new Client(nullptr, ui->ip_lineEdit->text(), ui->port_lineEdit->text().toUShort());
    m_client->setName(ui->name_lineEdit->text());
    m_client->connect2host();

    ptrWarGame = new WarGame(m_client);

    this->hide();
    ptrWarGame->show();
}

//menjam
bool Join::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->join_pop2_button && event->type()==QEvent::Enter){
        ui->join_pop2_button->setCursor(Qt::PointingHandCursor);
        ui->join_pop2_button->setStyleSheet(joinStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->back_pop2_button && event->type()==QEvent::Enter){
        ui->back_pop2_button->setCursor(Qt::PointingHandCursor);
        ui->back_pop2_button->setStyleSheet(backStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->join_pop2_button && event->type()==QEvent::Leave){
        ui->join_pop2_button->setStyleSheet(joinStyle);
    }
    else if(obj==ui->back_pop2_button && event->type()==QEvent::Leave){
        ui->back_pop2_button->setStyleSheet(backStyle);
    }

    return QDialog::eventFilter(obj,event);
}

