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

    // Translates coordinates of function so that coordinate origin is in (currX, currY) point
    void translatePoints(double coorX, double coorY);

public:
    // Constructs a function based on input string function, with coordinate origin in (coorX, coorY)
    // starting from x = 0, until x = endX, with numX linspaced coordinates
    Function(std::string function, double startX = 0, double endX = 20, int numX = 100, double coorX = 0, double coorY = 0);

    // TODO: vidi da li je mozda bolje da imamo 3 konstruktora:
    // ovaj jedan za sve
    // za WarGame(function, coorX, coorY) default: startX = 0, endX =15, num = 100
    // za GuessGame(startX, endX) default vrednosti: num = 100, coorX = 0, coorY = 0

    // Destructor (if needed, uncomment)
    // ~Function();

    QVector<QPointF> points();

};

#endif // FUNCTION_H
