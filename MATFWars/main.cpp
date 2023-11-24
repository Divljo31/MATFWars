#include "mainwindow.h"

#include <QApplication>

#include "Function.h"

double MySqr(double a_fVal) {  return a_fVal*a_fVal; }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Function f("x^2 + 2", -10, 10, 100, 0, 0);

//    for (QPointF point : f.points()) {
//        std::cout << point.x() << ", ";
//    }
//    std::cout << std::endl;

    for (QPointF point : f.points()) {
        std::cout << point.y() << ", ";
    }
    std::cout << std::endl;

//    double fVal;
//    try
//    {
//        double var_a = 1;
//        mu::Parser p;
//        p.DefineVar("x", &var_a);
//        p.SetExpr("sin(x)");

//        for (std::size_t a=0; a<100; ++a)
//        {
//            var_a = a;  // Change value of variable a
//            std::cout << p.Eval() << std::endl;
//        }
//    }
//    catch (mu::Parser::exception_type &e)
//    {
//        std::cout << e.GetMsg() << std::endl;
//    }

    w.show();
    return a.exec();
}
