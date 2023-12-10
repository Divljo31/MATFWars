#include "leaderboard.h"
#include "ui_leaderboard.h"

Leaderboard::Leaderboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Leaderboard)
{
    ui->setupUi(this);

}

Leaderboard::~Leaderboard()
{
    delete ui;

}

