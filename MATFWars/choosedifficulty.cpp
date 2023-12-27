#include "choosedifficulty.h"
#include "ui_choosedifficulty.h"

ChooseDifficulty::ChooseDifficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDifficulty)
{
    ui->setupUi(this);
    ptrGuessGame=new GuessGame();

    ui->go_difficulty_button->installEventFilter(this);
    ui->back_difficulty_button->installEventFilter(this);
    goStyle=ui->go_difficulty_button->styleSheet();
    backStyle=ui->back_difficulty_button->styleSheet();

    connect(ptrGuessGame, &GuessGame::backGuessClicked, this, &ChooseDifficulty::show);
    connect(ptrGuessGame, &GuessGame::menuGuessFromResult, this, &ChooseDifficulty::on_back_difficulty_button_clicked);
}

ChooseDifficulty::~ChooseDifficulty()
{
    delete ui;
    delete ptrGuessGame;
}

void ChooseDifficulty::on_go_difficulty_button_clicked()
{
    if(ui->easy_radioButton->isChecked())
        ptrGuessGame->setDifficulty(easy);
    else
        ptrGuessGame->setDifficulty(hard);
    ptrGuessGame->show();
    ptrGuessGame->startGuessGame();
    this->hide();
}

bool ChooseDifficulty::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->go_difficulty_button && event->type()==QEvent::Enter){
        ui->go_difficulty_button->setCursor(Qt::PointingHandCursor);
        ui->go_difficulty_button->setStyleSheet(goStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->back_difficulty_button && event->type()==QEvent::Enter){
        ui->back_difficulty_button->setCursor(Qt::PointingHandCursor);
        ui->back_difficulty_button->setStyleSheet(backStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->go_difficulty_button && event->type()==QEvent::Leave){
        ui->go_difficulty_button->setStyleSheet(goStyle);
    }
    else if(obj==ui->back_difficulty_button && event->type()==QEvent::Leave){
        ui->back_difficulty_button->setStyleSheet(backStyle);
    }

    return QDialog::eventFilter(obj,event);
}

void ChooseDifficulty::on_back_difficulty_button_clicked()
{
    this->hide();
    emit backDifficultyClicked();
}

