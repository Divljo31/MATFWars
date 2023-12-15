#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame)
{
    ui->setupUi(this);
    ptrCheck=new Check();

    connect(ptrCheck,&Check::noButtonClicked,this,&WarGame::show);

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

Player* WarGame::generatePlayer(int x, int y)
{
    Player *player = new Player("name");
    player->setCoordinates(randomPoint(x, y, 1.0));
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

void WarGame::on_quit_war_button_clicked()
{
    ptrCheck->show();
}

