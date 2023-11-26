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
    explicit WaitingRoom(QWidget *parent = nullptr);
    ~WaitingRoom();

signals:
    void backWaitingRoomClicked();

private slots:
    void on_play_wait_button_clicked();

    void on_back_wait_button_clicked();

private:
    Ui::WaitingRoom *ui;
    WarGame *ptrWarGame;
};

#endif // WAITINGROOM_H
