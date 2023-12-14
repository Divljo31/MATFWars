#include "Function.h"

Function::Function(std::string functionString,  double startX, double endX, int numX, double newCoorX, double newCoorY) {
    try {
        m_parser.DefineVar("x", &m_varX);
        m_parser.SetExpr(functionString);
        setPoints(startX, endX, numX);

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

// ovo koristimo za pointOfView igraca koji puca, bez fixedY bi bilo iz pointOfView posmatraca!!!!!!!!!!!
void Function::translatePointsPlayerView(double coorX, double coorY) {

    double fixedY = points().at(0).y();

    for (QPointF &point : m_points) {
        double currentX = point.x();
        double currentY = point.y();
        point.setX(currentX + coorX);

        point.setY(currentY + coorY - fixedY);
    }
}

void Function::translatePointsObserverView(double coorX, double coorY) {
    for (QPointF &point : m_points) {
        double currentX = point.x();
        double currentY = point.y();
        point.setX(currentX + coorX);

        point.setY(currentY + coorY);
    }
}

// MOZDA za war game treba da bude drugaciji gridWidth, u smislu da se ne koristi ceo vec samo jedan deo njega
void Function::scaleToCanvas(double width, double height, double gridWidth) {
    for (QPointF &point : m_points) {
        double currentX = point.x();
        double currentY = point.y();

        // ovo 30 je ustvari sirina canvasa
        point.setX(currentX*width/gridWidth);

        point.setY(-currentY*width/gridWidth);
    }
}

bool Function::equals(Function* other) {

    if (this->points().size() != other->points().size()) {
        return false;
    }

    double tolerance = 1e-5;

    for (int i = 0; i < this->points().size(); ++i) {
        if (std::abs(this->points().at(i).x() - other->points().at(i).x()) > tolerance ||
            std::abs(this->points().at(i).y() - other->points().at(i).y()) > tolerance) {
            return false;
        }
    }

    return true;
}

















