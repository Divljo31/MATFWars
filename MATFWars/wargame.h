#ifndef WARGAME_H
#define WARGAME_H

#include <QDialog>
#include <QVector>
#include "Client.h"
#include "FunctionNode.h"
#include "ObstacleNode.h"
#include "Player.h"
#include "Obstacle.h"

//menjano
#include <QLineEdit>
#include <QPushButton>

#include "PlayerNode.h"
#include "check.h"
#include "winner.h"
#include <QGraphicsScene>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class WarGame;
}

class WarGame : public QDialog
{
    Q_OBJECT

public:
    explicit WarGame(Client* client, QWidget *parent = nullptr);
    ~WarGame();
    void sendMessage();
    void setClient(Client *newClient);


    void startWarGame();

    void createObstacleJsonArray(QJsonArray *obstaclesJson);
    void extractPlayerJson(QJsonObject jsonObj);

    void setFromCreate(bool newFromCreate);

private:
    Player* generatePlayer(QString name, int width, int height);
    void generateObstacles(int width, int height);
    QPointF randomPoint(int width, int height, double playerOrObstacle);
    bool allowedObstacle(Obstacle* o);
    bool allowedPlayer(Player* p);
    void cleanUp();
    void flipCanvas();
    void drawCanvas();
    void collisionDetection(Function* f);
    bool isPointInCircle(QPointF p, QPointF center, double radius);
    QPointF getFirePosition();

private:
    Player* player0 = nullptr;
    Player* player1 = nullptr;
    Player* playerWinner = nullptr;
    int currentPlayer = 0;
    QSet<Obstacle*> obstacles;
    QGraphicsScene *m_canvas  = nullptr;
    int gridWidth = 30;
    int gridHeight = 18;

    bool m_fromCreate = false;

signals:
    void backWarClicked();
    void newPlayerIsSet(PlayerNode* playerNode);
    void newObstacleIsSet(ObstacleNode* obstacleNode);
    void newFunctionIsSet(FunctionNode* functionNode);
    void setCoordinateSystem();
    void cleanUpCanvas();
    void setUpGame(QString setUpDataString);
    void gameEnded(QString winnerName);

private slots:
    void on_back_war_button_clicked();
    void on_quit_war_button_clicked();
    void inputTaken();
    void fireFunction(std::string fString);
    void clientReceivedMessage(QString msg);


private:
    Ui::WarGame *ui;
    Check *ptrCheck = nullptr;
    Winner *ptrWinner = nullptr;
    
    Client *m_client;
    
    QString backStyle;
    QString fireStyle;
    QString quitStyle;
    QString chatStyle;

    void switchPlayer();

    void setCanvas();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;


};

#endif // WARGAME_H
