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

    yesStyle=ui->yes_check_button->styleSheet();
    noStyle=ui->no_check_button->styleSheet();
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
        ui->yes_check_button->setStyleSheet(yesStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->no_check_button && event->type()==QEvent::Enter){
        ui->no_check_button->setCursor(Qt::PointingHandCursor);
        ui->no_check_button->setStyleSheet(noStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->yes_check_button && event->type()==QEvent::Leave){
        ui->yes_check_button->setStyleSheet(yesStyle);
    }
    else if(obj==ui->no_check_button && event->type()==QEvent::Leave){
        ui->no_check_button->setStyleSheet(noStyle);
    }

    return QDialog::eventFilter(obj,event);
}
