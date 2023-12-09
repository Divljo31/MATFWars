#ifndef GUESSGAME_H
#define GUESSGAME_H

#include <QDialog>
#include "Timer.h"

namespace Ui {
class GuessGame;
}

class GuessGame : public QDialog
{
    Q_OBJECT

public:
    explicit GuessGame(QWidget *parent = nullptr);
    ~GuessGame();

signals:
    void backGuessClicked();
    void guessGameStart();

private slots:
    void on_back_guess_button_clicked();


private:
    Ui::GuessGame *ui;
    Timer *m_timer;
};

#endif // GUESSGAME_H
