#ifndef DIFFICULT_H
#define DIFFICULT_H

#include <QDialog>

namespace Ui {
class Difficulty;
}

class Difficulty : public QDialog
{
    Q_OBJECT

public:
    explicit Difficulty(QWidget *parent = nullptr);
    ~Difficulty();

private:
    Ui::Difficulty *ui;
};

#endif // DIFFICULT_H
