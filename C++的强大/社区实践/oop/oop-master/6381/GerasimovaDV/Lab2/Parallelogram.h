#ifndef OOP_PARALLELOGRAM_H
#define OOP_PARALLELOGRAM_H

#include "Shape.h"

class Parallelogram : public Shape {
public:
    Parallelogram(Point* p1, Point* p2, Point* p3, Color* color, int id);

    Point* getCenterPoint() override;

    float area() override;

    ostream& printShape(ostream& stream, Shape& figure) const override {
        stream << fixed << setprecision(3);
        stream << "Фигура: параллелограмм" << endl;
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


#endif //OOP_PARALLELOGRAM_H
