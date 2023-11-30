#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QDialog>

namespace Ui {
class Leaderboard;
}

class Leaderboard : public QDialog
{
    Q_OBJECT

public:
    explicit Leaderboard(QWidget *parent = nullptr);
    ~Leaderboard();

private:
    Ui::Leaderboard *ui;
};

#endif // LEADERBOARD_H
