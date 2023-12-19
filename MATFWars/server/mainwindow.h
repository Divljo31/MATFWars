#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "Server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_stopServer_clicked();
    void on_pushButton_startServer_clicked();
    void on_pushButton_testConn_clicked();
    void smbConnectedToServer();
    void gotNewMesssage(QString msg);
    void disconnection();


private:
    Ui::MainWindow *ui;
    Server *server;
};

#endif // MAINWINDOW_H
