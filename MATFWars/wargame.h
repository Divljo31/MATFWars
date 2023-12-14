#ifndef WARGAME_H
#define WARGAME_H

#include <QDialog>
#include <QVector>
#include "PlayerWar.h"
#include "Obstacle.h"
#include "Client.h"

//menjano
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QMessageBox>

namespace Ui {
class WarGame;
}

class WarGame : public QDialog
{
    Q_OBJECT

public:
    explicit WarGame(QWidget *parent = nullptr);
    ~WarGame();

    static bool startGame();
    static bool addPlayer();
    static bool removePlayer();
    static bool endGame();

    QVector<Obstacle> generateObstacles(int x, int y);
    PlayerWar generatePlayer(int x, int y);
    QPointF randomPoint(int x, int y, float playerOrObstacle);


    PlayerWar player1() const;

    PlayerWar player2() const;

    Obstacle getObstacle(size_t index) const;


signals:
    void backWarClicked();

private slots:
    void on_back_war_button_clicked();

private:
    Ui::WarGame *ui;
    PlayerWar m_player1;
    PlayerWar m_player2;
    QVector<Obstacle> m_obstacles;

};

#endif // WARGAME_H
