#ifndef CREATE_H
#define CREATE_H

#include <QDialog>
#include <QEnterEvent>
#include "waitingroom.h"
#include "Client.h"

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
    void clientCreated(Client *client);

private slots:
    void on_back_pop1_button_clicked();
    void on_create_pop1_button_clicked();

    void gotError(QAbstractSocket::SocketError err);

private:
    Ui::Create *ui;
    WarGame *ptrWarGame;
    QString backStyle;
    QString createStyle;

//menjam
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    Client* m_client;
    QString m_lastUserName;
};



#endif // CREATE_H
