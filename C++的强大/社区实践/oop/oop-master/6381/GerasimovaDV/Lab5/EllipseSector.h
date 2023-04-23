#ifndef OOP_ELLIPSESECTOR_H
#define OOP_ELLIPSESECTOR_H

#include "Shape.h"

class EllipseSector : public Shape {
public:
    EllipseSector(Point* center, float R1, float R2, float start_angle, float end_angle, Color* color, int id);

    Point* getCenterPoint() override;

    float area() override;

    ostream& printShape(ostream& stream, Shape& figure) const override {
        stream << fixed << setprecision(3);
        stream << "Фигура: сектор эллипса" << endl;
        stream << "Идентификационный номер объекта: " << figure.getId() << endl;
        stream << "Цвет фигуры: " << figure.getColor()->getRed() << " " << figure.getColor()->getGreen() << " "
               << figure.getColor()->getBlue() << endl;
        stream << "Координаты, задающие фигуру:" << endl;
        for(Point* point : figure.getPoints()) {
            stream << "(" << point->x() << ";" << point->y() << ")" << endl;
        }
        return stream;
    }

private:
    float rad;
};



#endif //OOP_ELLIPSESECTOR_H
