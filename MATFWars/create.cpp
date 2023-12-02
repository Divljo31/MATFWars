#include "create.h"
#include "ui_create.h"

Create::Create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create),
    m_client(new Client(this))
{
    ui->setupUi(this);
    ptrWaitingRoom=new WaitingRoom();

    connect(ptrWaitingRoom,&WaitingRoom::backWaitingRoomClicked,this,&Create::show);

    connect(ui->create_pop1_button, &QPushButton::clicked, this, &Create::attemptConnection);

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


QString Create::lastUserName() const
{
    return m_lastUserName;
}

void Create::setLastUserName(const QString &newLastUserName)
{
    m_lastUserName = newLastUserName;
}


void Create::attemptConnection()
{

    const QString userName = ui->name_lineEdit->text();
    this->setLastUserName(userName);

    bool ok;
    const quint16 port = ui->port_lineEdit->text().toUShort(&ok);
    if (!ok)
        return;

    QHostAddress serverAddress = QHostAddress::LocalHost;


    ui->create_pop1_button->setEnabled(false);
    m_client->connectToServer(serverAddress, port);

}




