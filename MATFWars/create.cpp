#include "create.h"
#include "ui_create.h"

Create::Create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create)
{
    ui->setupUi(this);

    //menjam
    ui->create_pop1_button->installEventFilter(this);
    ui->back_pop1_button->installEventFilter(this);
    createStyle=ui->create_pop1_button->styleSheet();
    backStyle=ui->back_pop1_button->styleSheet();
}



Create::~Create()
{
    delete ui;
    if(ptrWarGame != nullptr)
        delete ptrWarGame;
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

    ptrWarGame= new WarGame(m_client);

    ptrWarGame->setFromCreate(true);
    ptrWarGame->show();
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

    return QDialog::eventFilter(obj, event);
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


