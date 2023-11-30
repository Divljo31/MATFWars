#include "wargame.h"
#include "ui_wargame.h"

WarGame::WarGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarGame)
{
    ui->setupUi(this);
    //menjano!!!
    //lineEdit=new QLineEdit();
    //enterButton=new QPushButton();

    //connect(lineEdit, &QLineEdit::returnPressed, this, &WarGame::on_fire_war_button_pressed);
    //connect(enterButton, &QPushButton::clicked, this, &WarGame::on_fire_war_button_clicked);

}

WarGame::~WarGame()
{
    delete ui;
    //delete lineEdit;
    //delete enterButton;
}

void WarGame::on_back_war_button_clicked()
{
    emit backWarClicked();
    this->hide();
}


//void WarGame::on_fire_war_button_clicked()
//{
    //QString text= lineEdit->text();
    //emit sendData(text);
    //ui->y_lineEdit->clear();
//}


//void WarGame::on_fire_war_button_pressed()
//{
    //QString text= lineEdit->text();
    //emit sendData(text);
    //ui->y_lineEdit->clear();

//}

