#ifndef FUNCTION_H
#define FUNCTION_H

#include <QVector>
#include <string>
#include "lib/muparser/muParser.h"

class Function
{
private:
    std::string m_function;
    mu::Parser m_parser;
    double m_var_x;

private:
    // Evaluates the function at a given x value
    double eval(double val_x);

public:
    // Constructor
    Function(std::string function);

    // Destructor (if needed, uncomment)
    // ~Function();

    // Generates a linearly spaced QVector of x-coordinates
    QVector<double> linspaceXCoords(double start, double end, int num);

    // Generates a linearly spaced QVector of y-coordinates corresponding to the x-coordinates
    QVector<double> linspaceYCoords(double start, double end, int num);
};

#endif // FUNCTION_H
