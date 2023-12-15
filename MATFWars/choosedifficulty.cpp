#include "choosedifficulty.h"
#include "ui_choosedifficulty.h"

ChooseDifficulty::ChooseDifficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDifficulty)
{
    ui->setupUi(this);
    ptrGuessGame=new GuessGame();
    ui->go_difficulty_button->installEventFilter(this);
    goStyle=ui->go_difficulty_button->styleSheet();
}

ChooseDifficulty::~ChooseDifficulty()
{
    delete ui;
    delete ptrGuessGame;
}

void ChooseDifficulty::on_go_difficulty_button_clicked()
{
    ptrGuessGame->show();
    ptrGuessGame->startGuessGame();
    this->hide();

}
//menjam
bool ChooseDifficulty::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->go_difficulty_button && event->type()==QEvent::Enter){
        ui->go_difficulty_button->setCursor(Qt::PointingHandCursor);
        ui->go_difficulty_button->setStyleSheet(goStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->go_difficulty_button && event->type()==QEvent::Leave){
        ui->go_difficulty_button->setStyleSheet(goStyle);
    }

    return QDialog::eventFilter(obj,event);
}
