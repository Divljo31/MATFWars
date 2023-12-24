#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "warchoose.h"
#include "leaderboard.h"
#include "settings.h"
#include "choosedifficulty.h"



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

    //void on_guess_game_button_clicked();

    void on_leaderboard_main_button_clicked();

    void on_tool_button_clicked();


    void on_guess_game_button_clicked();

private:
    Ui::MainWindow *ui;
    WarChoose *ptrWarChoose = nullptr;
    ChooseDifficulty *ptrChooseDifficulty = nullptr;
    Leaderboard *ptrLeaderboard = nullptr;
    Settings *ptrSettings = nullptr;
    QString warStyle;
    QString guessStyle;
    QString leaderboardStyle;




protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // MAINWINDOW_H
