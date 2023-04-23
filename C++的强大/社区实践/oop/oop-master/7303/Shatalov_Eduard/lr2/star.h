#pragma once

#include "shape.h"
#include <cmath>

class Star:public Shape{
public:
    int dot1x,dot1y;
    Star(double x = 0, double y = 0, double r_angle = 0.0, Color color = Color(), double radius = 1.0, double radius2 = 1.0) :
        Shape(x, y, r_angle, color),
        s_radius(radius),
        s_radius2(radius2)
        {
        dot1x = x+s_radius;
        dot1y = y;
    }

    Star(const Star &item):
        Shape(item.s_x, item.s_y, item.rotation_angle, item.s_color),
        s_radius(item.s_radius),
        s_radius2(item.s_radius2)
    {
    }

    Star& operator=(Star& item) {
        s_color = item.s_color;
        rotation_angle = item.rotation_angle;
        s_x = item.s_x;
        s_y = item.s_y;
        s_radius = item.s_radius;
        s_radius2 = item.s_radius2;
        return *this;
    }

    Star& operator++(int) {
        Star* a = new Star(*this);
        ++(*this);
        a->id = this->id;
        id_counter--;
        return *a;
    }

    Star& operator++() override {
        ++s_radius;
        ++s_radius2;
        return *this;
    }
    void scale(double coefficient) override;

    void rotate(double angle) override;

    ~Star() override = default;
private:
    std::ostream& printShape(std::ostream& stream = std::cout) override{
        stream << "Звезда с внешним радиусом " << s_radius << " и внутренним "<< s_radius2 << " с центром в координатах (" << this->s_x << ',' << this->s_y << ")" << " и повернута на угол " << this->rotation_angle << " градусов\n" << "Координаты 1 пика: ("<<dot1x <<", " << dot1y << "). Цвет - " << this->s_color << " id - " << get_id() << std::endl<<std::endl;
        return stream;
    }
    double s_radius;
    double s_radius2;

};

