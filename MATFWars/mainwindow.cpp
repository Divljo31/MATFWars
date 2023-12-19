#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrWarChoose=new WarChoose();
    ptrChooseDifficulty=new ChooseDifficulty();
    ptrLeaderboard=new Leaderboard();
    ptrSettings=new Settings();
   // ptrGuessGame=new GuessGame();

    //menjam
    ui->war_game_button->installEventFilter(this);
    ui->guess_game_button->installEventFilter(this);
    ui->leaderboard_main_button->installEventFilter(this);
    ui->tool_button->installEventFilter(this);

    // menjam
    connect(ptrWarChoose, &WarChoose::backChooseClicked, this, &MainWindow::show);
    //connect(ptrGuessGame, &GuessGame::backGuessClicked, this, &MainWindow::show);
    connect(ptrChooseDifficulty, &ChooseDifficulty::backDifficultyClicked, this, &MainWindow::show);

    warStyle=ui->war_game_button->styleSheet();
    guessStyle=ui->guess_game_button->styleSheet();
    leaderboardStyle=ui->leaderboard_main_button->styleSheet();
}



MainWindow::~MainWindow()
{
    delete ui;
    delete ptrWarChoose;
    delete ptrChooseDifficulty;
    delete ptrLeaderboard;
    delete ptrSettings;

}


void MainWindow::on_war_game_button_clicked()
{
    // menjam
    this->hide();
    ptrWarChoose->show();


}




//void MainWindow::on_guess_game_button_clicked()
//{
   // this->hide();
   // ptrGuessGame->show();
  //  ptrGuessGame->startGuessGame();

//
//}


void MainWindow::on_leaderboard_main_button_clicked()
{
    ptrLeaderboard->showLeaderboard();
    ptrLeaderboard->show();
}


void MainWindow::on_tool_button_clicked()
{
    ptrSettings->show();

}

//menjam
bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->war_game_button && event->type()==QEvent::Enter){
        ui->war_game_button->setCursor(Qt::PointingHandCursor);
        ui->war_game_button->setStyleSheet(warStyle+"border: 5px solid;");
    }
    else if(obj==ui->guess_game_button && event->type()==QEvent::Enter){
        ui->guess_game_button->setCursor(Qt::PointingHandCursor);
        ui->guess_game_button->setStyleSheet(guessStyle+"border: 5px solid;");
    }
    else if(obj==ui->leaderboard_main_button && event->type()==QEvent::Enter){
        ui->leaderboard_main_button->setCursor(Qt::PointingHandCursor);
        ui->leaderboard_main_button->setStyleSheet(leaderboardStyle+"border: 8px solid rgb(59, 23, 23);");
    }
    else if(obj==ui->tool_button && event->type()==QEvent::Enter){
        ui->tool_button->setCursor(Qt::PointingHandCursor);
    }
    else if(obj==ui->war_game_button && event->type()==QEvent::Leave){
        ui->war_game_button->setStyleSheet(warStyle);
    }
    else if(obj==ui->guess_game_button && event->type()==QEvent::Leave){
        ui->guess_game_button->setStyleSheet(guessStyle);
    }
    else if(obj==ui->leaderboard_main_button && event->type()==QEvent::Leave){
        ui->leaderboard_main_button->setStyleSheet(leaderboardStyle);
    }

    return QMainWindow::eventFilter(obj,event);
}




void MainWindow::on_guess_game_button_clicked()
{
    ptrChooseDifficulty->show();
    this->hide();
}

