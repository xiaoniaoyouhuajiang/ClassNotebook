#ifndef SHAPES_H
#define SHAPES_H


#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <cstdint>
using namespace std;


struct point
{
    double x;
    double y;
    bool operator ==(const point other) const {
        if (x == other.x && y == other.y) return 1;
        else return 0;
    }
    bool operator !=(const point other) const {
        if (x != other.x || y != other.y) return 1;
        else return 0;
    }
};


//абстрактный класс
class Shape
{

public:

    Shape(point icenter): center(icenter)
    {
        color[0] = color[1] = color[2] = 0;
    }

    //изменение центра фигуры
    void move_center(point icenter)
    {

        //перемещение каждой точки
        for(auto& p : arr_point)
        {
            p.x += center.x - icenter.x;
            p.y += center.y - icenter.y;
        }

        //изменение центра
        this->center = icenter;

    }

    //поворот фигуры на заданный угол против часовой стрелки относительно центра фигуры
    virtual void rotation(double angle)
    {
        if( angle == 360 || angle == 0 ) return;

        double rad_angle = angle * M_PI / 180;
        double curr_x, curr_y;
        for( auto& p : arr_point )
        {
            curr_x = center.x + (p.x-center.x)*cos(rad_angle)-(p.y-center.y)*sin(rad_angle);
            curr_y = center.y + (p.x-center.x)*sin(rad_angle)+(p.y-center.y)*cos(rad_angle);
            p.x = curr_x;
            p.y = curr_y;
        }
    }

    //масштабирование фигуры на заданный коэффициент
    virtual void zoom( double z )
    {
        for(auto& p : arr_point)
        {
            p.x = z * (p.x - center.x) + center.x;
            p.y = z * (p.y - center.y) + center.y;
        }
    }

    //установка цвета
    void set_color( unsigned int r, unsigned int g, unsigned int b )
    {
         color[0] = r;
         color[1] = g;
         color[2] = b;
    }

    //получение цвета
    void get_color(unsigned int& r, unsigned int& g, unsigned int& b)
    {
        r = color[0];
        g = color[1];
        b = color[2];
    }

    //оператор вывода в поток
    virtual void output(ostream& out)
    {
        out << "Center: (" << center.x << ", " << center.y << ")" << "\n";
        out << "RGB Color: " << color[0] << ", " << color[1] << ", " << color[2] << "\n";
        out << "Point number: " << arr_point.size() << "\n";
        out << "Points: \n";
        for(auto p : arr_point)
            out << "(" << p.x << ", " << p.y << ")\n";
    }

    friend ostream& operator<<(ostream& out, Shape& sh)
    {
        sh.output(out);
        return out;
    }

    point get_center() {
        return center;
    }

 protected:

    point center;
    //координаты точек относительно системы координат
    vector<point> arr_point;
    unsigned int color[3];

};


//треугольник, задается по трем точкам
class Triangle : public Shape
{
public:
    Triangle( double x1, double y1, double x2, double y2, double x3, double y3 )
            : Shape( {(x1+x2+x3)/3, (y1+y2+y3)/3} )
    {
        arr_point.push_back( { x1, y1 } );
        arr_point.push_back( { x2, y2 } );
        arr_point.push_back( { x3, y3 } );
     }

};


//параллелограмм, задается по трем точкам
class Parallelogram : public Shape
{
public:
    Parallelogram( double x1, double y1, double x2, double y2, double x3, double y3 )
            : Shape( {(x1+x3)/2, (y1+y3)/2} )
    {
        arr_point.push_back( { x1, y1 } );
        arr_point.push_back( { x2, y2 } );
        arr_point.push_back( { x3, y3 } );
        point D = {2*center.x - x2, 2*center.y - y2};
        arr_point.push_back(D);
     }

};


//ромб, задается по двум точкам смежным и острому углу
class Rhombus : public Shape
{
public:
    Rhombus( double x1, double y1, double x2, double y2, double angle ): Shape({0, 0}), r_angle(angle)
    {
        arr_point.push_back( { x1, y1 } );
        arr_point.push_back( { x2, y2 } );
        point A;
        double rad_angle = angle * M_PI / 180;
        A.x = (x2 - x1)*cos(rad_angle) - (y2 - y1)*sin(rad_angle) + x1;
        A.y = (x2 - x1)*sin(rad_angle) + (y2 - y1)*cos(rad_angle) + y1;
        arr_point.push_back(A);

        center.x = (x2 + A.x)/2;
        center.y = (y2+ A.y)/2;

        point D = {2*center.x - x1, 2*center.y - y1};
        arr_point.push_back(D);

     }

    //оператор вывода в поток
    virtual void output(std::ostream& out)
    {
        out << "Center: (" << center.x << ", " << center.y << ")" << "\n";
        out << "RGB Color: " << color[0] << ", " << color[1] << ", " << color[2] << "\n";
        out << "Angle: " << r_angle << "\n";
        out << "Point number: " << arr_point.size() << "\n";
        out << "Points: \n";
        for(auto p : arr_point)
            out << "(" << p.x << ", " << p.y << ")\n";
    }

private:
    double r_angle;
};

#endif // SHAPES_H
