#ifndef JOIN_H
#define JOIN_H

#include <QDialog>
#include "waitingroom.h"
#include "Client.h"

namespace Ui {
class Join;
}

class Join : public QDialog
{
    Q_OBJECT

public:
    explicit Join(QWidget *parent = nullptr);
    ~Join();

signals:
    void backJoinPop2Clicked();


private slots:
    void on_back_pop2_button_clicked();

    void on_join_pop2_button_clicked();

private:
    Ui::Join *ui;
    WaitingRoom *ptrWaitingRoom;
    Client* m_client;
    
    QString backStyle;
    QString joinStyle;

 //menjam
 protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

};

#endif // JOIN_H
