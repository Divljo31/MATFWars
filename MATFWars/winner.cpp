#include "winner.h"
#include "ui_winner.h"


Winner::Winner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Winner)
{
    ui->setupUi(this);
    quitStyle=ui->quit_winner_button->styleSheet();
    ui->quit_winner_button->installEventFilter(this);
    connect(ui->quit_winner_button,&QPushButton::clicked,this,&Winner::on_quit_winner_button_clicked);

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
    ui->label->setText("Congratulations " + winnerName + " !");
}

void Winner::on_quit_winner_button_clicked()
{
    QApplication::quit();
}

bool Winner::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->quit_winner_button && event->type()==QEvent::Enter){
        ui->quit_winner_button->setCursor(Qt::PointingHandCursor);
        ui->quit_winner_button->setStyleSheet(quitStyle+"border:4px solid rgb(180, 72, 72);");
    }
    else if(obj==ui->quit_winner_button && event->type()==QEvent::Leave){
        ui->quit_winner_button->setStyleSheet(quitStyle);
    }

    return QDialog::eventFilter(obj, event);
}
