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
    ptrSettings=new Settings();
    // menjam
    connect(ptrWarChoose, &WarChoose::backChooseClicked, this, &MainWindow::show);
    connect(ptrGuessGame, &GuessGame::backGuessClicked, this, &MainWindow::show);
}



MainWindow::~MainWindow()
{
    delete ui;
    delete ptrWarChoose;
    delete ptrGuessGame;
    delete ptrLeaderboard;
    delete ptrSettings;
}


void MainWindow::on_war_game_button_clicked()
{
    // menjam
    this->hide();
    ptrWarChoose->show();
}


void MainWindow::on_guess_game_button_clicked()
{
    this->hide();
    ptrGuessGame->show();
    ptrGuessGame->startGuessGame();
}


void MainWindow::on_leaderboard_main_button_clicked()
{
    ptrLeaderboard->show();
}


void MainWindow::on_tool_button_clicked()
{
    ptrSettings->show();
}

