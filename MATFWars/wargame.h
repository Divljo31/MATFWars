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
    static bool bothConnected;
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

    //chat
    //void attemptConnection();
    //void connectedToServer();
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void userLeft(const QString &username);


private:
    Ui::WarGame *ui;
    PlayerWar m_player1;
    PlayerWar m_player2;
    QVector<Obstacle> m_obstacles;

    //chat
    Client *m_chatClient;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;


};

#endif // WARGAME_H
