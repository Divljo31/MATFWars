#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QDialog>
#include "wargame.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingRoom(Client *client, QWidget *parent = nullptr);
    ~WaitingRoom();

    void setClient(Client *newClient);

signals:
    void backWaitingRoomClicked();

private slots:
    void on_play_wait_button_clicked();

    void on_back_wait_button_clicked();

    void clientConnected(QString str);

private:
    Ui::WaitingRoom *ui;
    WarGame *ptrWarGame;
    Client *m_client;
    
    QString playStyle;
    QString backStyle;

//menjam
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

};

#endif // WAITINGROOM_H
