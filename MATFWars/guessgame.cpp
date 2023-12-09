#include "guessgame.h"
#include "ui_guessgame.h"

GuessGame::GuessGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuessGame)
{
    ui->setupUi(this);
    m_timer = new Timer();
    m_timer->setInterfejs(ui);
    m_timer->start();
    connect(m_timer, SIGNAL(tajmerIstekao()), this, SLOT(on_back_guess_button_clicked()));
    //connect(this,SIGNAL(guessGameStart()),m_timer,SLOT(start()));
}

GuessGame::~GuessGame()
{
    delete ui;

}

void GuessGame::on_back_guess_button_clicked()
{
    emit backGuessClicked();
    this->hide();
}

