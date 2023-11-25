#ifndef JOIN_H
#define JOIN_H

#include <QDialog>

namespace Ui {
class Join;
}

class Join : public QDialog
{
    Q_OBJECT

public:
    explicit Join(QWidget *parent = nullptr);
    ~Join();

private:
    Ui::Join *ui;
};

#endif // JOIN_H
