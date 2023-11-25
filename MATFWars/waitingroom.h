#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QDialog>

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingRoom(QWidget *parent = nullptr);
    ~WaitingRoom();

private:
    Ui::WaitingRoom *ui;
};

#endif // WAITINGROOM_H
