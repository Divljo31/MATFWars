#ifndef WINNER_H
#define WINNER_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
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

private slots:
    void on_quit_winner_button_clicked();

private:
    Ui::Winner *ui;
    QString quitStyle;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    QString winnerName = "";

};

#endif // WINNER_H
