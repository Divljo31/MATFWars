#ifndef CREATE_H
#define CREATE_H

#include <QDialog>
#include <QHostAddress>
#include "Client.h"

#include "waitingroom.h"

namespace Ui {
class Create;
}

class Create : public QDialog
{
    Q_OBJECT

public:
    explicit Create(QWidget *parent = nullptr);
    ~Create();

    // menjam
    QString lastUserName() const;
    void setLastUserName(const QString &newLastUserName);

signals:
    void backCreatePop1Clicked();

private slots:
    void on_back_pop1_button_clicked();

    void on_create_pop1_button_clicked();

    void attemptConnection();


private:
    Ui::Create *ui;
    WaitingRoom *ptrWaitingRoom;
    Client* m_client;
    QString m_lastUserName;


};

#endif // CREATE_H
