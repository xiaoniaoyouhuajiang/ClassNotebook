#include "mainwindow.h"
#include <QApplication>
#include "right_triangle.h"
#include "ellipse.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
        Triangle tmp({50, 50, 50}, 10, 10, 50, 50, 100, 10);
        Triangle tmpp({25, 25, 25}, 20, 20, 100, 100, 100, 10);
        std::cout << tmp << tmpp;
        Triangle result = tmp + tmpp;
        std::cout << result;

        double b = 55.55;
        Triangle add = tmp + b;
        std::cout << add;
    */
    /*
        Ellipse tmp1({0, 0, 255}, -100.1, -100.1, 100.1, 300.1);
        std::cout << tmp1;
        Ellipse add = tmp1 + 55.55;
        std::cout << add;
    */

        RightTriangle tmp2({255, 0, 128}, 100, 100, 50, 120);
        std::cout << tmp2;
        RightTriangle tmp3 = tmp2 + 55.55;
        std::cout << tmp3;

    MainWindow w;
    w.show();

    return a.exec();
}
