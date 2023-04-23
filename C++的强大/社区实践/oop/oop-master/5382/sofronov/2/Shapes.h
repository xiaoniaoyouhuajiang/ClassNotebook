#pragma once

#include <iostream>
#include <math.h>

enum Color {red, green, blue};

struct Point
{
    Point () {}
    Point (double x, double y) : x(x), y(y) {}
    double x;
    double y;
};


class Shape {
public:
    Shape(Color c):_id(_last_id++), _color(c)
    {}


    virtual void move (Point) = 0;
    virtual void rotate (double) = 0 ;
    virtual void zoom (double) = 0;

    bool doinsert(const Shape& other) {
        double left_one = this->themostleftx();
        double right_one = this->themostrightx();
        double left_two = other.themostleftx();
        double right_two = other.themostrightx();
        if ((left_one<=left_two && right_one>=left_two) || (left_one<=right_two && right_one>=right_two))
            return true;
        if ((left_two<=left_one && right_two>=left_one) || (left_two<=right_one && right_two>=right_one))
            return true;
        return false;
    }

    virtual double const themostleftx() const = 0;
    virtual double const themostrightx() const = 0;

    void getcolor() const{
        switch (_color) {
            case red: {
                std::cout << "красный";
                break;
            }
            case blue: {
                std::cout << "синий";
                break;
            }
            case green: {
                std::cout << "зелёный";
                break;
            }
        }
    }
    virtual ~Shape() {}

protected:
    static int _last_id;
    int _id;
    Color _color;
};

class Arc: public Shape {
public:
    Arc(Point center, Point start, double angle, Color c): Shape(c), _angle(angle), _start(start), _center(center)
    {}

    void move(Point new_coordinates)  {
        _center=new_coordinates;
        _start.x+=new_coordinates.x-_center.x;
        _start.y+=new_coordinates.y-_center.y;
    }

    void rotate(double rotate_angle) {
        Point tmp_start(_start.x,_start.y);
        Point tmp_center(_center.x,_center.y);

        _start.x=tmp_start.x*cos(rotate_angle) - tmp_start.y*sin(rotate_angle);
        _start.y=tmp_start.x*sin(rotate_angle) + tmp_start.y*cos(rotate_angle);

        _center.x=tmp_center.x*cos(rotate_angle) - tmp_center.y*sin(rotate_angle);
        _center.y=tmp_center.x*sin(rotate_angle) + tmp_center.y*cos(rotate_angle);
    }

    void zoom(double coefficient) {
        double dx = _start.x-_center.x;
        double dy = _start.y-_center.y;
        _start.x+=dx*(coefficient-1);
        _start.y+=dy*(coefficient-1);
    }

    friend std::ostream& operator<< (std::ostream &out, Arc const& a) {
        out << "Дуга \nЦентр в точке с координатами (" << a._center.x << ", " << a._center.y << ") \n";
        out << "Начало в точке с координатами (" << a._start.x << ", " << a._start.y << ") \n";
        out << "Угол поворота равен " << a._angle << " \n";
        out << "id = " << a._id << "\n";
        out << "Цвет ";
        a.getcolor();
        out << " \n \n";
        return out;
    }

    double const themostleftx() const {
        double radius = (sqrt(pow(_center.x-_start.x,2)+pow(_center.y-_start.y,2)));
        return (_center.x-radius);
    }

    double const themostrightx() const {
        double radius = (sqrt(pow(_center.x-_start.x,2)+pow(_center.y-_start.y,2)));
        return (_center.x+radius);
    }

private:
    Point _center; // Центр
    Point _start; // Начало
    double _angle; // угол
};

class Circle: public Shape {
public:
    Circle(Point center, double radius, Color c):Shape(c), _radius(radius), _center(center)
    {}

    void move(Point new_coordinates) {
        _center=new_coordinates;
    }

    void rotate(double rotate_angle) {
        Point tmp_center(_center.x,_center.y);

        _center.x=tmp_center.x*cos(rotate_angle) - tmp_center.y*sin(rotate_angle);
        _center.y=tmp_center.x*sin(rotate_angle) + tmp_center.y*cos(rotate_angle);
    }

    void zoom(double coefficient) {
        _radius*=coefficient;
    }

    friend std::ostream& operator<< (std::ostream &out, Circle const& a) {
        out << "Круг \nЦентр в точке с координатами (" << a._center.x << ", " << a._center.y << ") \n";
        out << "Радиус равен " << a._radius << " \n";
        out << "id = " << a._id << "\n";
        out << "Цвет ";
        a.getcolor();
        out << " \n \n";
        return out;
    }

    double const themostleftx() const {
        return (_center.x-_radius);
    }

    double const themostrightx() const {
        return (_center.x+_radius);
    }

private:
    Point _center; //центр
    double _radius; //радиус
};

class Ellipse: public Shape {
public:
    Ellipse(Point left_focus, Point right_focus, Color c): Shape(c) {
        if (left_focus.x > right_focus.x)
            std::swap(left_focus,right_focus);
        _left_focus=left_focus;
        _right_focus=right_focus;
    }

    void move(Point new_center) {
        Point old_center((_left_focus.x+_right_focus.x)/2, (_left_focus.y+_right_focus.y)/2);
        double dx = new_center.x - old_center.x;
        double dy = new_center.y - old_center.y;
        _left_focus.x+=dx;
        _left_focus.y+=dy;
        _right_focus.x+=dx;
        _right_focus.y+=dy;
    }

    void rotate(double rotate_angle) {
        Point tmp_right_focus(_right_focus.x,_right_focus.y);
        Point tmp_left_focus(_left_focus.x,_left_focus.y);

        _right_focus.x=tmp_right_focus.x*cos(rotate_angle) - tmp_right_focus.y*sin(rotate_angle);
        _right_focus.y=tmp_right_focus.x*sin(rotate_angle) + tmp_right_focus.y*cos(rotate_angle);

        _left_focus.x=tmp_left_focus.x*cos(rotate_angle) - tmp_left_focus.y*sin(rotate_angle);
        _left_focus.y=tmp_left_focus.x*sin(rotate_angle) + tmp_left_focus.y*cos(rotate_angle);
    }

    void zoom(double coefficient) {
        Point center((_left_focus.x+_right_focus.x)/2, (_left_focus.y+_right_focus.y)/2);
        double dx = _left_focus.x-center.x;
        double dy = _left_focus.y-center.y;
        _left_focus.x+=dx*(coefficient-1);
        _left_focus.y+=dy*(coefficient-1);

        dx = _right_focus.x-center.x;
        dy = _right_focus.y-center.y;
        _right_focus.x+=dx*(coefficient-1);
        _right_focus.y+=dy*(coefficient-1);

    }

    friend std::ostream& operator<< (std::ostream &out, Ellipse const& a) {
        out << "Эллипс \nФокусы в точках с координатами (" << a._left_focus.x << ", " << a._left_focus.y << ") и (" << a._right_focus.x << ", " << a._right_focus.y << ")\n";
        out << "id = " << a._id << "\n";
        out << "Цвет ";
        a.getcolor();
        out << " \n \n";
        return out;
    }

    double const themostleftx() const {
        return (_left_focus.x);
    }

    double const themostrightx() const {
        return (_right_focus.x);
    }

private:
    Point _left_focus; //левый фокус
    Point _right_focus; //правый фокус
};
