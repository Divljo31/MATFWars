#ifndef WARGAME_H
#define WARGAME_H

#include <QDialog>
#include <QVector>
#include "Player.h"
#include "Obstacle.h"
#include "Client.h"

//menjano
#include <QLineEdit>
#include <QPushButton>

#include "check.h"

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
    Player* generatePlayer(int x, int y);
    QPointF randomPoint(int x, int y, float playerOrObstacle);

 //   Obstacle getObstacle(size_t index) const;


signals:
    void backWarClicked();

private slots:
    void on_back_war_button_clicked();



    void on_quit_war_button_clicked();

private:
    Ui::WarGame *ui;
    Check *ptrCheck;
};

#endif // WARGAME_H
