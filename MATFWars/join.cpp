#include "join.h"
#include "ui_join.h"

Join::Join(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Join)
{


    ui->setupUi(this);
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

    m_client = new Client(nullptr, "localhost", ui->port_lineEdit->text().toUShort());
    m_client->setName(ui->name_lineEdit->text());
    m_client->connect2host();

    ptrWaitingRoom=new WaitingRoom(m_client);
    ptrWaitingRoom->show();
}

