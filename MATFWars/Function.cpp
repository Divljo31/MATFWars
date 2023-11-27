#include "Function.h"

Function::Function(std::string functionString,  double startX, double endX, int numX, double newCoorX, double newCoorY) {
    try {
        m_parser.DefineVar("x", &m_varX);
        m_parser.SetExpr(functionString);
        setPoints(startX, endX, numX);
        translatePoints(newCoorX, newCoorY);

    } catch (mu::Parser::exception_type &e) {
        std::cerr << e.GetMsg() << std::endl;
        //TODO: show invalid function message
    }
}

double Function::eval(double val_x) {
    try {
        m_varX = val_x;
        return m_parser.Eval();
    } catch (mu::Parser::exception_type &e) {
        std::cerr << e.GetMsg() << std::endl;
        return 0;
        //TODO: show invalid function message
    }
}

QVector<double> Function::getXCoords(double start, double end, int num) {
    QVector<double> xCoords(num);

    if (num == 0) return xCoords;

    if (num == 1) {
        xCoords[0] = start;
        return xCoords;
    }

    double delta = (end - start) / (num - 1);

    for (int i = 0; i < num - 1; i++)
        xCoords[i] = start + delta*i;
    xCoords[num - 1] = end;

    return xCoords;
};

QVector<double> Function::getYCoords(double start, double end, int num) {
    QVector<double> xCoords = getXCoords(start, end, num);
    QVector<double> yCoords(num);

    for (int i = 0; i < num - 1; i ++) {
        yCoords[i] = eval(xCoords[i]);
    }

    yCoords[num-1] = eval(xCoords[num-1]);

    return yCoords;
}

void Function::setPoints(double start, double end, int num) {
    QVector<double> xCoords = getXCoords(start, end, num);
    QVector<double> yCoords = getYCoords(start, end, num);

    for (int i = 0; i < num; i++) {
        double x = xCoords[i];
        double y = yCoords[i];

        m_points.append(QPointF(x, y));
    }

    // TODO: mozda ovde da bude i translatePoints
}

QVector<QPointF> Function::points() {
    return m_points;
}

void Function::translatePoints(double coorX, double coorY) {

    double fixedY = points().at(0).y();

    for (QPointF &point : m_points) {
        double currentX = point.x();
        double currentY = point.y();
        point.setX(currentX + coorX); // ovo je ok

        // TODO: proveriti kada budemo imali WarGame VAZNO!!!
        point.setY(currentY + coorY - fixedY);
    }
}















