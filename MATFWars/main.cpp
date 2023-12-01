#include "mainwindow.h"
#include "wargame.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    WarGame wargame;
    PlayerWar player = wargame.generatePlayer(25, 15);
    std::cout << player.coordinates().x() << " , " << player.coordinates().y()<< std::endl;

    return a.exec();
}
