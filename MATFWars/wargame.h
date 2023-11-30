#ifndef WARGAME_H
#define WARGAME_H

#include <QDialog>
//menjano
#include <QLineEdit>
#include <QPushButton>
namespace Ui {
class WarGame;
}

class WarGame : public QDialog
{
    Q_OBJECT

public:
    explicit WarGame(QWidget *parent = nullptr);
    ~WarGame();

signals:
    void backWarClicked();
    //void sendData(const QString& text);

private slots:
    void on_back_war_button_clicked();

    void on_fire_war_button_clicked();

    void on_fire_war_button_pressed();


private:
    Ui::WarGame *ui;
    //menjano!!!
    //QLineEdit *lineEdit;
    //QPushButton *enterButton;
};

#endif // WARGAME_H
