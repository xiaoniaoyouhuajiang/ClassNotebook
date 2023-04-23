#pragma once

#include "shape.h"
class Ellipse : public Shape {
public:
    Ellipse(double x = 0, double y = 0, double r_angle = 0.0, const Color& color = Color(), double a = 1.0, double b = 1.0) :
        Shape(x, y, r_angle, color),
        e_a(a),
        e_b(b)
    {
    }

    Ellipse(const Ellipse& item) :
        Shape(item.s_x, item.s_y, item.rotation_angle, item.s_color),
        e_a(item.e_a),
        e_b(item.e_b)
    {
        rotation_angle = item.rotation_angle;
    }

    Ellipse& operator=(Ellipse& item) {
        e_a = item.e_a;
        e_b = item.e_b;
        rotation_angle = item.rotation_angle;
        s_x = item.s_x;
        s_y = item.s_y;
        return *this;
    }
    Ellipse& operator++(int) {
        Ellipse* a = new Ellipse(*this);
        ++(*this);
        a->id = this->id;
        id_counter--;
        return *a;
    }

    Ellipse& operator++(){
        ++e_a;
        ++e_b;
        return *this;
    }
    void scale(double coefficient) override;

    ~Ellipse() override = default;

private:
    std::ostream& printShape(std::ostream& stream = std::cout) override {
        stream << "Эллипс с параметрами " << e_a << " , " << e_b << " и центром в координатах (" << this->s_x << "," << this->s_y << ")" << " повернут на угол " << this->rotation_angle << " градусов" << ".\nЦвет - " << this->s_color << " id - " << get_id() << std::endl<<std::endl;
        return stream;
    }

    double e_a;
    double e_b;
};
