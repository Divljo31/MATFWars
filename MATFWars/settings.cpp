#include "settings.h"
#include "ui_settings.h"

QColor Settings::funcColor = QColor(0,0,255);
QColor Settings::obstColor = QColor(Qt::darkCyan);

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->func_color_button->installEventFilter(this);
    funcStyle=ui->func_color_button->styleSheet();

    ui->obst_color_button->installEventFilter(this);
    obstStyle=ui->obst_color_button->styleSheet();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_func_color_button_clicked()
{
    QColor newColor = QColorDialog::getColor(Qt::white);
    if (newColor.isValid()) {
        Settings::funcColor = newColor;
    }
}

void Settings::on_obst_color_button_clicked()
{
    QColor newColor = QColorDialog::getColor(Qt::white);
    if (newColor.isValid()) {
        Settings::obstColor=newColor;
    }
}

bool Settings::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->func_color_button && event->type()==QEvent::Enter){
        ui->func_color_button->setCursor(Qt::PointingHandCursor);
        ui->func_color_button->setStyleSheet(funcStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->func_color_button && event->type()==QEvent::Leave){
        ui->func_color_button->setStyleSheet(funcStyle);
    }
    else if(obj==ui->obst_color_button && event->type()==QEvent::Enter){
        ui->obst_color_button->setCursor(Qt::PointingHandCursor);
        ui->obst_color_button->setStyleSheet(obstStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->obst_color_button && event->type()==QEvent::Leave){
        ui->obst_color_button->setStyleSheet(obstStyle);
    }


    return QDialog::eventFilter(obj,event);
}


