#ifndef WARCHOOSE_H
#define WARCHOOSE_H

#include <QDialog>
#include "create.h"
#include "join.h"


namespace Ui {
class WarChoose;
}

class WarChoose : public QDialog
{
    Q_OBJECT

public:
    explicit WarChoose(QWidget *parent = nullptr);
    ~WarChoose();

// menjano
signals:
    void backChooseClicked();

private slots:
    void on_create_choose_button_clicked();

    void on_join_choose_button_clicked();

    void on_back_choose_button_clicked();

private:
    Ui::WarChoose *ui;
    Create *ptrCreate;
    Join *ptrJoin;


};

#endif // WARCHOOSE_H
