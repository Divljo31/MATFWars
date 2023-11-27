#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrWarChoose=new WarChoose();
    ptrGuessGame=new GuessGame();
    ptrLeaderboard=new Leaderboard();

    // menjam
    connect(ptrWarChoose, &WarChoose::backChooseClicked, this, &MainWindow::show);
}



MainWindow::~MainWindow()
{
    delete ui;
    delete ptrWarChoose;
    delete ptrGuessGame;
    delete ptrLeaderboard;

}


void MainWindow::on_war_game_button_clicked()
{
    // menjam
    this->hide();
    ptrWarChoose->show();
}


void MainWindow::on_guess_game_button_clicked()
{
    ptrGuessGame->show();
}


void MainWindow::on_leaderboard_main_button_clicked()
{
    ptrLeaderboard->show();
}

