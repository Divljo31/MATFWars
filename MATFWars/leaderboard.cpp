#include "leaderboard.h"
#include "ui_leaderboard.h"

Leaderboard::Leaderboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Leaderboard)
{
    ui->setupUi(this);
}

Leaderboard::~Leaderboard()
{
    delete ui;

}

void Leaderboard::showLeaderboard()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/../MATFWars/txt/leaderboard.txt";

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString fileContent = stream.readAll();

        ui->leaderboard_textEdit->setHtml(fileContent);

        file.close();
    }
    else
    {
        qDebug() << "Error opening file in showLeaderboard():" << file.errorString();
    }
}

