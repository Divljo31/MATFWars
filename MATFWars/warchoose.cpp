#include "warchoose.h"
#include "ui_warchoose.h"

WarChoose::WarChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarChoose)
{
    ui->setupUi(this);
}

WarChoose::~WarChoose()
{
    delete ui;
}
