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

//Obstacle WarGame::getObstacle(size_t index) const
//{
//    return m_obstacles.at(index);
//}

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
