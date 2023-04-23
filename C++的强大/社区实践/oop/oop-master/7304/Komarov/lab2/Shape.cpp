//
// Created by user on 31.03.19.
//

#include "Shape.h"



//unsigned long int iii=0;

   Shape::Shape(Point center,Color color ):color(color), center(center) {
        static long int i = 0;
        id = i;
        i++;
    }
    void Shape::set_color(Color color) {
        this->color = color;
    }

    Color Shape::get_color() const {
        return color;
    }

    unsigned long int Shape::get_id() const {
        return id;
    }
    void Shape::moving(Point p) {
        double offset_by_x = p.get_x() - center.get_x();
        double offset_by_y = p.get_y() - center.get_y();
        for (size_t i = 0; i < points.size(); i++) {
            double tmp_x = points[i].get_x() + offset_by_x;
            double tmp_y = points[i].get_y() + offset_by_y;
            points[i].setter_x(tmp_x);
            points[i].setter_y(tmp_y);
        }
        center = p;
    }

    void Shape::rotation(double grade) {
        double grade_in_rad = grade*M_PI/180.0;
        for (size_t i = 0; i < points.size(); i++) {
            double x =center.get_x()+(points[i].get_x()-center.get_x())*cos(grade_in_rad)-(points[i].get_y()-center.get_y())*sin(grade_in_rad);
            double y = center.get_y() + (points[i].get_x() - center.get_x())*sin(grade_in_rad) + (points[i].get_y() - center.get_y())*cos(grade_in_rad); ;
            points[i].setter_x(x);
            points[i].setter_y(y);
        }
    }

    std::ostream& operator << (ostream& stream, Shape& shape) {
        stream << "Object id: " << shape.get_id()<<endl;
        stream << endl << "(x, y): " << shape.center.get_x() << ", " << shape.center.get_y() << endl;
        stream << "Цвет фигуры: " << shape.color.get_R() << " " << shape.color.get_G() << " " << shape.color.get_B()<< endl;
        stream <<endl<< "Координаты фигуры: " << endl;
        for (size_t i = 0; i < shape.points.size(); i++) {
            stream<< "Point:"<<i+1 << "(" << shape.points[i].get_x() << ";" << shape.points[i].get_y() << ")" << endl;
        }
        return stream;
    }

    Shape  & Shape:: operator +(const double ch){
    this->center.setter_x(center.get_x()+ch);
    this->center.setter_y(center.get_y()+ch);

    for (auto& pt : points) {
        pt.setter_x(pt.get_x()+ch);
        pt.setter_y(pt.get_y()+ch);
    }
   return *this;
}


