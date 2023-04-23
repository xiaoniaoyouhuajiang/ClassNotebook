#pragma once
#include "shape.h"
class Sector : public Shape {
public:
    Sector(double x = 0, double y = 0, double r_angle = 0.0, Color color = Color(), double radius = 1.0, double angle = 360.0) :
        Shape(x, y, r_angle, color),
        s_angle(angle),
        s_radius(radius)
    {
    }

    Sector(const Sector& item):
        Shape(item.s_x, item.s_y, item.rotation_angle, item.s_color),
        s_angle(item.s_angle),
        s_radius(item.s_radius)
    {
    }

    Sector& operator=(Sector& item) {
        s_angle = item.s_angle;
        s_color = item.s_color;
        rotation_angle = item.rotation_angle;
        s_radius = item.s_radius;
        s_x = item.s_x;
        s_y = item.s_y;
        return *this;
    }

    void scale(double coefficient) override;
    Sector& operator++(int) {
        Sector* a = new Sector(*this);
        ++(*this);
        a->id = this->id;
         id_counter--;
        return *a;

    }
    Sector& operator++(){
        ++s_radius;
        ++s_angle;
        return *this;
    }
    ~Sector() override = default;

private:
    std::ostream& printShape(std::ostream& stream = std::cout) override{
        stream << "Сектор круга с углом " << s_angle << " и радиусом " << s_radius << " с центром в координатах (" << this->s_x << ',' << this->s_y << ")" << " и повернут на угол " << this->rotation_angle << " градусов" << ". \nЦвет - " << this->s_color << " id - " << get_id() << std::endl<< std::endl;
        return stream;
    }

    double s_angle;
    double s_radius;
};

