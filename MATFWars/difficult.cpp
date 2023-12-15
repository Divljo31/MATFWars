#include "difficult.h"
#include "ui_difficulty.h"

Difficulty::Difficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Difficulty)
{
    ui->setupUi(this);
}

Difficulty::~Difficulty()
{
    delete ui;
}
