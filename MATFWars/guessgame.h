#ifndef GUESSGAME_H
#define GUESSGAME_H

#include <QDialog>

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

private slots:
    void on_back_guess_button_clicked();

private:
    Ui::GuessGame *ui;
};

#endif // GUESSGAME_H
