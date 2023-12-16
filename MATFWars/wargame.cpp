#include "wargame.h"
#include "Canvas.h"
#include "ObstacleNode.h"
#include "PlayerNode.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame),
    m_canvas(new Canvas(this))
{
    ui->setupUi(this);
    ptrCheck=new Check();

    //menjam
    ui->fire_war_button->installEventFilter(this);
    ui->quit_war_button->installEventFilter(this);
    ui->back_war_button->installEventFilter(this);

    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);
    connect(this, &WarGame::newPlayerIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::addPlayer);
    connect(this, &WarGame::newObstacleIsSet, dynamic_cast<Canvas *>(m_canvas), &Canvas::addObstacle);

    backStyle=ui->back_war_button->styleSheet();
    quitStyle=ui->quit_war_button->styleSheet();
    fireStyle=ui->fire_war_button->styleSheet();

    ui->gvCanvas->setRenderHints(QPainter::Antialiasing);
    ui->gvCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    m_canvas->setSceneRect(ui->gvCanvas->rect());
    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);
}

WarGame::~WarGame()
{
    delete ui;
    delete ptrCheck;

}

void WarGame::startWarGame()
{
    m_canvas->setSceneRect(ui->gvCanvas->rect());
    ui->gvCanvas->setBackgroundBrush(QBrush(Qt::white));
    ui->gvCanvas->setScene(m_canvas);

    player0 = generatePlayer(30, 20);
    player1 = generatePlayer(30, 20);

    generateObstacles(30, 20);

    PlayerNode *pn0 = new PlayerNode(player0);
    emit newPlayerIsSet(pn0);

    PlayerNode *pn1 = new PlayerNode(player0);
    emit newPlayerIsSet(pn1);

    for(Obstacle* o : obstacles) {
        ObstacleNode *on = new ObstacleNode(o);
        emit newObstacleIsSet(on);
    }

    dynamic_cast<Canvas *>(m_canvas)->addCoordinateSystem();
}

//Obstacle WarGame::getObstacle(size_t index) const
//{
//    return m_obstacles.at(index);
//}

void WarGame::generateObstacles(int width, int height)
{
    int numOfObstacles = QRandomGenerator::global()->bounded(8);

    for(int i = 0; i < numOfObstacles; i++){
        Obstacle* obstacle = new Obstacle();

        obstacle->setCenter(randomPoint(width, height, 1.0));
        obstacle->setCenter(QPointF(i, i));
        double newDiameter = obstacle->generateDiameter(numOfObstacles);
        obstacle->setDiameter(2.0);

        obstacles.push_back(obstacle);
    }
}

Player* WarGame::generatePlayer(int width, int height)
{
    Player *player = new Player("name");

    QPointF playerPos = randomPoint(width, height, 0.3);
    player->setCoordinates(playerPos);
    return player;
}

// x-> width, y -> height, playerOrObstacle -> procenat ekrana gde moze da se generise
QPointF WarGame::randomPoint(int width, int height, float areaPercent)
{
    //if generatePlayer is the caller function, then playerOrObstacle = 1.0, else  playerOrObstacle = 2.0
    float xCoord = QRandomGenerator::global()->generateDouble();
    xCoord = (-width/2 + 1) + xCoord * areaPercent * (width/2);

    float yCoord = QRandomGenerator::global()->generateDouble();
    yCoord = (-height/2 + 1) + yCoord * (height/2) * 0.9;

    QPointF pointF(xCoord, yCoord);

    return pointF;

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
