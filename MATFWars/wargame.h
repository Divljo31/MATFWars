#ifndef WARGAME_H
#define WARGAME_H

#include <QDialog>

namespace Ui {
class WarGame;
}

class WarGame : public QDialog
{
    Q_OBJECT

public:
    explicit WarGame(QWidget *parent = nullptr);
    ~WarGame();

private:
    Ui::WarGame *ui;
};

#endif // WARGAME_H
