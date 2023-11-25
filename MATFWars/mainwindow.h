#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "warchoose.h"
#include "guessgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_war_game_button_clicked();

    void on_guess_game_button_clicked();

private:
    Ui::MainWindow *ui;
    WarChoose *ptrWarChoose;
    GuessGame *ptrGuessGame;

};
#endif // MAINWINDOW_H
