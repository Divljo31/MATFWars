#include "mainwindow.h"
#include "testwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    testWindow t;
    t.show();
    return a.exec();
}
