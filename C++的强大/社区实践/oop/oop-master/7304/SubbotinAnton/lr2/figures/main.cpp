#include <QCoreApplication>
#include "circle.h"
#include "parallelogram.h"
#include "regularhexagon.h"
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "fff";
    QCoreApplication a(argc, argv);
    Point centre(0.0,0.0);
    Point RH(2.0,3.0);
    Point RL(-2.0,2.0);
    double radius = 5.0;

    Circle circle(centre,radius);
    circle.setColor({1,7,3});
    circle.RotateOn(30.0);
    circle.ScaleOn(1.6);
    circle.Information(cout);
    circle.MoveTo({1,1});
    circle.Information(cout);

    Parallelogram parallelogram(centre, RH, RL);
    parallelogram.setColor({3,5,1});
    parallelogram.RotateOn(180);
    parallelogram.ScaleOn(1.6);
    parallelogram.Information(cout);
    parallelogram.MoveTo({1,1});
    parallelogram.Information(cout);

    RegularHexagon regularhexagon(centre, radius);
    regularhexagon.setColor({2,0,8});
    regularhexagon.RotateOn(30.0);
    regularhexagon.ScaleOn(1.6);
    regularhexagon.Information(cout);
    regularhexagon.MoveTo({1,1});
    regularhexagon.Information(cout);

    return a.exec();
}
