#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Leaderboard;
}

class Leaderboard : public QDialog
{
    Q_OBJECT

public:
    explicit Leaderboard(QWidget *parent = nullptr);
    ~Leaderboard();

public:
    void showLeaderboard();

private:
    Ui::Leaderboard *ui;
};

#endif // LEADERBOARD_H
