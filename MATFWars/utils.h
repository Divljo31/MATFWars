#ifndef UTILS_H
#define UTILS_H
#include <QPointF>

class Utils
{

public:
    Utils();


    // Na onu vrednost kolika je za WarGame
    constexpr static const double GRID_WIDTH = 30;
    constexpr static const double WIDTH = 708;
    constexpr static const double HEIGHT = 187;

    static QPointF setCanvasCoordiante(QPointF point)
    {
        // TODO: napravi Utils fajl sa gridWidth
        double sceneX = point.x()*WIDTH/GRID_WIDTH;
        sceneX += WIDTH/2;

        double sceneY = -point.y()*WIDTH/GRID_WIDTH;
        sceneY += HEIGHT/2;

        return QPointF(sceneX, sceneY);
    }

    static double getCanvasDiameter(double diameter) {
        return diameter*WIDTH/GRID_WIDTH;
    }
};

#endif // UTILS_H
