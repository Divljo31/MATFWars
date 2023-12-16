#ifndef CHOOSEDIFFICULTY_H
#define CHOOSEDIFFICULTY_H

#include <QDialog>
#include "guessgame.h"

namespace Ui {
class ChooseDifficulty;
}

class ChooseDifficulty : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDifficulty(QWidget *parent = nullptr);
    ~ChooseDifficulty();

private slots:
    void on_go_difficulty_button_clicked();



private:
    Ui::ChooseDifficulty *ui;
    GuessGame *ptrGuessGame;
    QString goStyle;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // CHOOSEDIFFICULTY_H
