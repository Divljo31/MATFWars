#include "create.h"
#include "ui_create.h"

Create::Create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create)
{
    ui->setupUi(this);

    //connect(ptrWaitingRoom,&WaitingRoom::backWaitingRoomClicked,this,&Create::show);


    //connect(m_client->m_socket, &QTcpSocket::errorOccurred, this, &Client::gotError);
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
    m_client = new Client(nullptr, "localhost", ui->port_lineEdit->text().toUShort());
    m_client->setName(ui->name_lineEdit->text());

    //emit(clientCreated(m_client));

    m_client->connect2host();

    this->hide();

    ptrWaitingRoom=new WaitingRoom(m_client);
    ptrWaitingRoom->show();
}



void Create::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
    case 0:
        strError = "Connection was refused";
        break;
    case 1:
        strError = "Remote host closed the connection";
        break;
    case 2:
        strError = "Host address was not found";
        break;
    case 5:
        strError = "Connection timed out";
        break;
    default:
        strError = "Unknown error";
    }

   // ui->textEdit_log->append(strError);
}


