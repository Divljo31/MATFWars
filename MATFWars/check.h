#ifndef CHECK_H
#define CHECK_H

#include <QDialog>

namespace Ui {
class Check;
}

class Check : public QDialog
{
    Q_OBJECT

public:
    explicit Check(QWidget *parent = nullptr);
    ~Check();

signals:
    void noButtonClicked();


private slots:
    void on_no_check_button_clicked();

    void on_yes_check_button_clicked();

private:
    Ui::Check *ui;
    QString yesStyle;
    QString noStyle;


//menjam
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

};

#endif // CHECK_H
