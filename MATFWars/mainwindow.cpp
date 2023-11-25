#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrWarChoose=new WarChoose();
    ptrGuessGame=new GuessGame();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrWarChoose;
    delete ptrGuessGame;
}


void MainWindow::on_war_game_button_clicked()
{
    ptrWarChoose->show();
}


void MainWindow::on_guess_game_button_clicked()
{
    ptrGuessGame->show();
}

