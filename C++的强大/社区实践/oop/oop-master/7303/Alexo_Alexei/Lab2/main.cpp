#include <QCoreApplication>
#include <iostream>
#include "color.h"
#include "ellipse.h"
#include "point.h"
#include "regularpentagon.h"
#include "shape.h"
#include "square.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Square square(Color(255, 10, 144), Point(50,50), 15);
    Ellipse ellipse(Color(255, 10, 144), Point(50,50), 15, 20);
    RegularPentagon regularrentagon(Color(255, 10, 144), Point(50,50), 15);
    Square square_(Color(255, 10, 144), Point(50,50), 15);
    cout << square << endl;
    square * 0.5;
    cout << square << endl;
    square + -5;
    cout << square << endl;
    square * 1;
    cout << square << endl;
    square * 3;
    cout << square << endl;

    square.Scale(0.5);
    cout << square << endl;
    square.Move(Point(100, 100));
    cout << square << endl;

    cout << ellipse << endl;
    ellipse * 2;
    cout << ellipse << endl;
    ellipse.Scale(0.5);
    cout << ellipse << endl;
    ellipse + 15;
    cout << ellipse << endl;

    cout << regularrentagon << endl;
    regularrentagon * 2;
    cout << regularrentagon << endl;
    regularrentagon * 1;
    cout << regularrentagon << endl;
    regularrentagon * 3;
    cout << regularrentagon << endl;
    regularrentagon + 10;
    cout << regularrentagon << endl;
    regularrentagon.Scale(0.5);
    cout << regularrentagon << endl;
    regularrentagon.Move(Point(100, 100));
    cout << regularrentagon << endl;

    cout << square_ << endl;

    cout << "END!" << endl;

    return a.exec();
}
