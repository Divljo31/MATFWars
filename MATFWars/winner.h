#ifndef WINNER_H
#define WINNER_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Confetti.h"
namespace Ui {
class Winner;
}

class Winner : public QDialog
{
    Q_OBJECT

public:
    explicit Winner(QWidget *parent = nullptr);
    ~Winner();


    QString getWinnerName() const;
    void setWinnerName(const QString &newWinnerName);

private:
    Ui::Winner *ui;

    QString winnerName;

};

#endif // WINNER_H
