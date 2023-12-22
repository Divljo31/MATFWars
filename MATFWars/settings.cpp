#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

     ui->func_color_button->installEventFilter(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_func_color_button_clicked()
{

    QColor ColorValue=QColorDialog::getColor(Qt::white,this,tr("Select Color"));
}

bool Settings::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->func_color_button && event->type()==QEvent::Enter){
        ui->func_color_button->setCursor(Qt::PointingHandCursor);
    }

    return QDialog::eventFilter(obj,event);
}
