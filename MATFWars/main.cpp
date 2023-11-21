#include "mainwindow.h"

#include <QApplication>

#include "lib/muparser/muParser.h"
#include "Function.h"

double MySqr(double a_fVal) {  return a_fVal*a_fVal; }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Function f("sin(x)^2 + cos(x)^2");

    for (double x : f.linspaceXCoords(-5, 5, 100))
        std::cout << x << " ";
    std::cout << std::endl;

    for (double x : f.linspaceYCoords(-5, 5, 100))
        std::cout << x << " ";
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
