#include "winner.h"
#include "ui_winner.h"


Winner::Winner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Winner)
{
    ui->setupUi(this);

}

Winner::~Winner()
{
    delete ui;
}

QString Winner::getWinnerName() const
{
    return winnerName;
}

void Winner::setWinnerName(const QString &newWinnerName)
{
    winnerName = newWinnerName;
    ui->label->setText("winner winner chicken dinner is " + winnerName + "!!!!!!!!");
}
