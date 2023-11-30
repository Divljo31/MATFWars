#include "mainwindow.h"
/*#include "wargame.h"
#include <iostream>*/
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*WarGame wargame;
    QVector<Obstacle> obstacles = wargame.generateObstacles(15, 25);
    for(Obstacle obstacle : obstacles){
        std::cout << obstacle.center().x() << " , " << obstacle.center().y()<< std::endl;
    }*/

    return a.exec();
}
