#include "guessgame.h"
#include "ui_guessgame.h"

GuessGame::GuessGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuessGame)
{
    ui->setupUi(this);
    m_timer = new Timer();
    m_timer->setInterfejs(ui);

    connect(m_timer, SIGNAL(tajmerIstekao()), this, SLOT(on_back_guess_button_clicked()));
}

void GuessGame::startGuessGame()
{
    m_timer->start();
    m_timer->resetujSek();
}

GuessGame::~GuessGame()
{
    delete ui;
    delete m_timer;
}

void GuessGame::on_back_guess_button_clicked()
{
    emit backGuessClicked();
    m_timer->prekiniBrojanje();
    ui->timer_label->setText(" ");
    this->hide();
}

