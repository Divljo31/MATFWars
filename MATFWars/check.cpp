#include "check.h"
#include "ui_check.h"

Check::Check(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Check)
{
    ui->setupUi(this);

    connect(ui->yes_check_button,&QPushButton::clicked,this,&Check::on_yes_check_button_clicked);
}

Check::~Check()
{
    delete ui;
}

void Check::on_no_check_button_clicked()
{
    emit noButtonClicked();
    this->hide();
}

void Check::on_yes_check_button_clicked()
{
    QApplication::quit();
}

