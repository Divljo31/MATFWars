#ifndef WARCHOOSE_H
#define WARCHOOSE_H

#include <QDialog>

namespace Ui {
class WarChoose;
}

class WarChoose : public QDialog
{
    Q_OBJECT

public:
    explicit WarChoose(QWidget *parent = nullptr);
    ~WarChoose();

private:
    Ui::WarChoose *ui;
};

#endif // WARCHOOSE_H
