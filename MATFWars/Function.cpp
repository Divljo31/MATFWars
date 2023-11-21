#include "Function.h"

Function::Function(std::string function) {
    try {
        m_parser.DefineVar("x", &m_var_x);
        m_parser.SetExpr(function);
    } catch (mu::Parser::exception_type &e) {
        std::cerr << e.GetMsg() << std::endl;
        //TODO: show invalid function message
    }

}

double Function::eval(double val_x) {
    try {
        m_var_x = val_x;
        return m_parser.Eval();
    } catch (mu::Parser::exception_type &e) {
        std::cerr << e.GetMsg() << std::endl;
        return 0;
        //TODO: show invalid function message
    }
}

QVector<double> Function::linspaceXCoords(double start, double end, int num) {
    QVector<double> linspaced(num);

    if (num == 0) return linspaced;

    if (num == 1) {
        linspaced[0] = start;
        return linspaced;
    }

    double delta = (end - start) / (num - 1);

    for (int i = 0; i < num - 1; i++)
        linspaced[i] = start + delta*i;
    linspaced[num - 1] = end;

    return linspaced;
}

QVector<double> Function::linspaceYCoords(double start, double end, int num) {
    QVector<double> linspacedX = linspaceXCoords(start, end, num);
    QVector<double> linspacedY(num);

    for (int i = 0; i < num - 1; i ++) {
        linspacedY[i] = eval(linspacedX[i]);
    }

    linspacedY[num-1] = eval(linspacedX[num-1]);

    return linspacedY;
}

