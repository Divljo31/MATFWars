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

signals:
    void backDifficultyClicked();

private slots:
    void on_go_difficulty_button_clicked();
    void on_back_difficulty_button_clicked();

private:
    Ui::ChooseDifficulty *ui;
    GuessGame *ptrGuessGame = nullptr;
    QString goStyle;
    QString backStyle;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // CHOOSEDIFFICULTY_H
