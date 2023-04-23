#ifndef OOP_ELLIPSE_H
#define OOP_ELLIPSE_H

#include "Shape.h"

class Ellipse : public Shape {
public:
    Ellipse(Point* center, float R1, float R2, Color* color, int id);

    Point* getCenterPoint() override;

    float area() override;

    ostream& printShape(ostream& stream, Shape& figure) const override {
        stream << fixed << setprecision(3);
        stream << "Фигура: эллипс" << endl;
        stream << "Идентификационный номер объекта: " << figure.getId() << endl;
        stream << "Цвет фигуры: " << figure.getColor()->getRed() << " " << figure.getColor()->getGreen() << " "
               << figure.getColor()->getBlue() << endl;
        stream << "Координаты, задающие фигуру:" << endl;
        for(Point* point : figure.getPoints()) {
            stream << "(" << point->x() << ";" << point->y() << ")" << endl;
        }
        return stream;
    }
};


#endif //OOP_ELLIPSE_H
