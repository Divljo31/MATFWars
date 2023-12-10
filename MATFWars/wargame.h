#ifndef WARGAME_H
#define WARGAME_H

#include <QDialog>
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
    explicit WarGame(QWidget *parent = nullptr);
    ~WarGame();

signals:
    void backWarClicked();

private slots:
    void on_back_war_button_clicked();



    void on_quit_war_button_clicked();

private:
    Ui::WarGame *ui;
    Check *ptrCheck;
};

#endif // WARGAME_H
