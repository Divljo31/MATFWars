#include "check.h"
#include "ui_check.h"

Check::Check(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Check)
{
    ui->setupUi(this);

    connect(ui->yes_check_button,&QPushButton::clicked,this,&Check::on_yes_check_button_clicked);

    //menjam
    ui->yes_check_button->installEventFilter(this);
    ui->no_check_button->installEventFilter(this);
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

//menjam
bool Check::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->yes_check_button && event->type()==QEvent::Enter){
        ui->yes_check_button->setCursor(Qt::PointingHandCursor);
    }
    else if(obj==ui->no_check_button && event->type()==QEvent::Enter){
        ui->no_check_button->setCursor(Qt::PointingHandCursor);
    }

    return QDialog::eventFilter(obj,event);
}
