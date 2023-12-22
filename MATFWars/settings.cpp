#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    ui->func_color_button->installEventFilter(this);
    funcStyle=ui->func_color_button->styleSheet();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_func_color_button_clicked()
{

    QColor ColorValue=QColorDialog::getColor(Qt::white,this,tr("Select Color"));
}

void Settings::on_obst_color_button_clicked()
{
    QColor ColorValue=QColorDialog::getColor(Qt::white,this,tr("Select Color"));

}

bool Settings::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->func_color_button && event->type()==QEvent::Enter){
        ui->func_color_button->setCursor(Qt::PointingHandCursor);
        ui->func_color_button->setStyleSheet(funcStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->func_color_button && event->type()==QEvent::Leave){
        ui->func_color_button->setStyleSheet(funcStyle);
    }


    return QDialog::eventFilter(obj,event);
}


