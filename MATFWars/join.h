#ifndef JOIN_H
#define JOIN_H

#include <QDialog>
#include "wargame.h"
#include "Client.h"
#include <QMessageBox>

namespace Ui {
class Join;
}

class Join : public QDialog
{
    Q_OBJECT

public:
    explicit Join(QWidget *parent = nullptr);
    ~Join();
    
    
    
    void popUpShow();
    
    void showPopUp();
    
signals:
    void backJoinPop2Clicked();


private slots:
    void on_back_pop2_button_clicked();

    void on_join_pop2_button_clicked();

    void clientReceivedMessage(QString msg);

private:
    Ui::Join *ui;
    WarGame *ptrWarGame = nullptr;
    Client* m_client;
    
    QString backStyle;
    QString joinStyle;


 //menjam
 protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

};

#endif // JOIN_H
