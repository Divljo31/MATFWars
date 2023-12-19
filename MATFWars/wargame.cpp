#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(Client *client, QWidget *parent) :
    QDialog(parent)
    , ui(new Ui::WarGame)
    , m_client(client)
{
    ui->setupUi(this);
    ptrCheck = new Check();

    ui->chat_textEdit->setReadOnly(true);
    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);
    connect(m_client, &Client::someMessage, this, &WarGame::clientReceivedMessage);
    connect(ui->chat_send_button, &QPushButton::clicked, this, &WarGame::sendMessage);
    connect(ui->chat_lineEdit, &QLineEdit::returnPressed, this, &WarGame::sendMessage);
}

WarGame::~WarGame()
{
    delete ui;
    delete ptrCheck;

}

QVector<Obstacle> WarGame::generateObstacles(int x, int y)
{
    int numOfObstacles = QRandomGenerator::global()->bounded(8);

    QVector<Obstacle> obstacleArray(numOfObstacles);

    for(Obstacle &obstacle : obstacleArray){

        obstacle.setCenter(randomPoint(x, y, 2.0));
        float newDiameter = obstacle.generateDiameter(numOfObstacles);
        obstacle.setDiameter(newDiameter);

    }

    return obstacleArray;
}

// range coords x i y
PlayerWar WarGame::generatePlayer(int x, int y)
{
    PlayerWar player;
    player.setCoordinates(randomPoint(x, y, 1.0));
    return player;
}

QPointF WarGame::randomPoint(int x, int y, float playerOrObstacle)
{
    //if generatePlayer is the caller function, then playerOrObstacle = 1.0, else  playerOrObstacle = 2.0
    float xCoord = QRandomGenerator::global()->generateDouble();
    xCoord = (-x) + xCoord * playerOrObstacle*x;
    float yCoord = QRandomGenerator::global()->generateDouble();
    yCoord = (-y) + yCoord * 2.0*y;

    QPointF pointF(xCoord, yCoord);

    return pointF;

}

void WarGame::on_back_war_button_clicked()
{
    emit backWarClicked();
    this->hide();
}

void WarGame::clientReceivedMessage(QString msg)
{
    int colonIndex = msg.indexOf(':');
    if(colonIndex != -1){
        QString name = msg.left(colonIndex);
        QString msgText = msg.right(msg.length() - colonIndex - 1);
        ui->chat_textEdit->append(tr("<font><b>") + name + tr(": </b>")+ msgText + tr("</font>"));
    }
    else{
        ui->chat_textEdit->append(msg);
    }
}

void WarGame::setClient(Client *newClient)
{
    m_client = newClient;
}

void WarGame::sendMessage()
{
    if (m_client->getStatus()) {
        // The socket is connected, proceed with sending the message
        QString message = ui->chat_lineEdit->text();
        m_client->sendClicked(m_client->name() + ": " + message);
        ui->chat_lineEdit->clear();

    } else {
        // Handle the case when the socket is not connected
        qDebug() << "Socket is not connected!";
    }
}


void WarGame::on_quit_war_button_clicked()
{
    ptrCheck->show();
}

