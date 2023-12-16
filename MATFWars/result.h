#ifndef RESULT_H
#define RESULT_H

#include <QDialog>

namespace Ui {
class Result;
}

class Result : public QDialog
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = nullptr);
    ~Result();

signals:
    void menuResultClicked();

private slots:
    void on_menu_result_button_clicked();

private:
    Ui::Result *ui;
};

#endif // RESULT_H
