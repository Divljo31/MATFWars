#ifndef FUNCTION_H
#define FUNCTION_H

#include <QVector>
#include <QPointF>
#include <string>
#include "lib/muparser/muParser.h"

class Function
{
private:
    mu::Parser m_parser;
    double m_varX;
    QVector<QPointF> m_points;
private:
    // Evaluates the function at a given x value
    double eval(double val_x);

    // Generates a linearly spaced QVector of x-coordinates from x = 0, to x = end
    QVector<double> getXCoords(double start, double end, int num);

    // Generates a linearly spaced QVector of y-coordinates corresponding to the x-coordinates
    QVector<double> getYCoords(double start, double end, int num);

    // Sets x,y coordinates of points of our function
    void setPoints(double start, double end, int num);

public:
    // Constructs a function based on input string function, with coordinate origin in (coorX, coorY)
    // starting from x = 0, until x = endX, with numX linspaced coordinates
    Function(std::string function, double startX = -15, double endX = 15, int numX = 1000);

    // Destructor (if needed, uncomment)
    // ~Function();

    QVector<QPointF> points();

    // Translates coordinates of function so that coordinate origin is in (currX, currY) point
    void translatePointsPlayerView(double coorX, double coorY);

    void translatePointsObserverView(double coorX, double coorY);

    void scaleToCanvas(double width, double height, double gridWidth);

    // Compares two functions based on points
    bool equals(Function* otherFunction);

};

#endif // FUNCTION_H
