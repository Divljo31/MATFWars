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

#include "check.h"

namespace Ui {
class WarGame;
}

class WarGame : public QDialog
{
    Q_OBJECT

public:
    explicit WarGame(Client* client, QWidget *parent = nullptr);
    ~WarGame();


    QVector<Obstacle> generateObstacles(int x, int y);
    PlayerWar generatePlayer(int x, int y);
    QPointF randomPoint(int x, int y, float playerOrObstacle);

    void sendMessage();

    void setClient(Client *newClient);


 //   Obstacle getObstacle(size_t index) const;


signals:
    void backWarClicked();

private slots:
    void on_back_war_button_clicked();

    void on_quit_war_button_clicked();

    void clientReceivedMessage(QString msg);



private:
    Ui::WarGame *ui;
    Check *ptrCheck;
    
    Client *m_client;
    
    QString backStyle;
    QString fireStyle;
    QString quitStyle;

//menjam
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;


};

#endif // WARGAME_H
