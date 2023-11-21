#include "join.h"
#include "ui_join.h"

Join::Join(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Join)
{
    ui->setupUi(this);
}

Join::~Join()
{
    delete ui;
}
