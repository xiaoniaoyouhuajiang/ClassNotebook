#ifndef SHAPE_H
#define SHAPE_H

#include <cmath>
#include "point.h"
#include "color.h"

class Shape
{
protected:
    Point centre;
    Color color;
    int angle;
    int ID;
    static int nextID;
    friend ostream& operator << (ostream& os, Shape& element)
    {
        element.info(os);
        return os;
    }

public:
    Shape() : color(0, 0, 0){
        ID = ++nextID;
    }
    ~Shape(){}

    virtual void Moving(Point dot) = 0;     //перемещение в указанные координаты
    virtual void Turn(double value) = 0;    //поворот на указанный угол против часовой стрелки
    virtual void toScale(double k) = 0;     //масштабирование на заданный коэффициент
    virtual void info(ostream& os) = 0;     //вывод информации

    void getColor()
    {
        cout << color;
    }

    void setColor(Color bloom)
    {
        color = bloom;
    }
};

#endif // SHAPE_H
