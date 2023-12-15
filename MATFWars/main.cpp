#include "mainwindow.h"
#include "wargame.h"
#include <iostream>
#include <QApplication>
#include "testwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    testWindow t;
    t.show();

    return a.exec();
}
