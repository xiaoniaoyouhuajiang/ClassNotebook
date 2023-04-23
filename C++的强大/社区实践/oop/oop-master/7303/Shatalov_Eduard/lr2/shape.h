#pragma once

#include <iostream>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0) :
        r(red),
        g(green),
        b(blue)
    {
    }

    Color(const Color& item) :
        r(item.r),
        g(item.g),
        b(item.b)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, const Color& color) {
        stream << '(' << int(color.r) << ',' << int(color.g) << ',' << int(color.b) << ')';
        return stream;
    }

};

class Shape {
public:

    void setCoordinates(double newX, double newY);

    Shape(double x = 0.0, double y = 0.0, double r_angle = 0.0, const Color& color = Color()) :
        s_x(x),
        s_y(y),
        id(id_counter++),
        s_color(color),
        rotation_angle(r_angle)
    {
    }

    virtual ~Shape() = default;

    void setColor(const Color& newColor);

    const Color getColor();

    virtual void rotate(double angle);

    virtual void scale(double) = 0;

    friend std::ostream& operator<<(std::ostream& stream, Shape& shape) {
        return shape.printShape(stream);
    }
    //virtual Shape& operator++(int) = 0;
    virtual Shape& operator++() = 0;
    int get_id();

protected:
    virtual std::ostream& printShape(std::ostream&) = 0;
    double s_x;
    double s_y;
    int id;
    Color s_color;
    double rotation_angle;
    static int id_counter;
};

