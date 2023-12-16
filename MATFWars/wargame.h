#ifndef WARGAME_H
#define WARGAME_H

#include <QDialog>
#include <QVector>
#include "ObstacleNode.h"
#include "Player.h"
#include "Obstacle.h"

//menjano
#include <QLineEdit>
#include <QPushButton>

#include "PlayerNode.h"
#include "check.h"
#include <QGraphicsScene>

namespace Ui {
class WarGame;
}

class WarGame : public QDialog
{
    Q_OBJECT

public:
    explicit WarGame(QWidget *parent = nullptr);
    ~WarGame();
 //   Obstacle getObstacle(size_t index) const;

    void startWarGame();

private:
    Player* generatePlayer(int width, int height);
    void generateObstacles(int width, int height);
    QPointF randomPoint(int width, int height, float playerOrObstacle);

    Player* player0;
    Player* player1;
    int currentPlayer = 0;

    QVector<Obstacle*> obstacles;
    QGraphicsScene *m_canvas;

signals:
    void backWarClicked();
    void newPlayerIsSet(PlayerNode* playerNode);
    void newObstacleIsSet(ObstacleNode* obstacleNode);

private slots:
    void on_back_war_button_clicked();
    void on_quit_war_button_clicked();

private:
    Ui::WarGame *ui;
    Check *ptrCheck;
    QString backStyle;
    QString fireStyle;
    QString quitStyle;

//menjam
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

};

#endif // WARGAME_H
