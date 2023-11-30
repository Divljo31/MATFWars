#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame)
{
    ui->setupUi(this);

}

WarGame::~WarGame()
{
    delete ui;

}

PlayerWar WarGame::player1() const
{
    return m_player1;
}

PlayerWar WarGame::player2() const
{
    return m_player2;
}

Obstacle WarGame::getObstacle(size_t index) const
{
    return m_obstacles.at(index);
}

QVector<Obstacle> WarGame::generateObstacles(int x, int y)
{
    int numOfObstacles = QRandomGenerator::global()->bounded(8);

    QVector<Obstacle> obstacleArray(numOfObstacles);

    for(Obstacle &obstacle : obstacleArray){

        obstacle.setCenter(randomPoint(x, y));
        float newDiameter = obstacle.generateDiameter(numOfObstacles);
        obstacle.setDiameter(newDiameter);

    }

    return obstacleArray;
}

QPointF WarGame::randomPoint(int x, int y)
{
    float xCoord = QRandomGenerator::global()->generateDouble();
    xCoord = (-x) + xCoord * 2.0*x;
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



