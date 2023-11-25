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

private:
    Ui::GuessGame *ui;
};

#endif // GUESSGAME_H
