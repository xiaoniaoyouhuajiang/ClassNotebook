#include <iostream>
#include <string>
#include <cmath>
#include <string>

using namespace std;

enum Color{RED, ORANGE, YELLOW, GREEN, BLUE, DARK_BLUE, VIOLET};

class Shape
{
public:
    Shape(double x, double y, double angle, Color color) : x(x), y(y), color(color)
    {
        id = ++next_id;
        if(angle >= 360.0)
            this->angle = angle - int(angle / 360) * 360;
        else
            this->angle = angle;
    }

    virtual ~Shape()
    {
    }

    void move(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    void rotate(double add_angle)
    {
        if(add_angle >= 360)
            add_angle = add_angle - int(add_angle / 360) * 360;
        if(angle + add_angle < 360.0)
            angle += add_angle;
        else
            angle = (angle + add_angle) - 360;
    }

    void col(Color const &c)
    {
        color = c;
    }

    string get_color() const
    {
        switch(color)
        {
            case Color::RED:
            return "Color: RED";

            case Color::ORANGE:
            return "Color: ORANGE";

            case Color::YELLOW:
            return "Color: YELLOW";

            case Color::GREEN:
            return "Color: GREEN";

            case Color::BLUE:
            return "Color: BLUE";

            case Color::DARK_BLUE:
            return "Color: DARK BLUE";

            case Color::VIOLET:
            return "Color: VIOLET";

        default:
            return "Unknown color";
        }
    }

    friend std::ostream & operator <<(std::ostream &out, Shape &shape)
    {
        out << "Object id: " << shape.id << endl << "(x, y): " << shape.x << ", " << shape.y << endl << "Angle with ox: " << shape.angle <<  " degrees" << endl << shape.get_color();
        return out;
    }

    //abstract method
    virtual void scaling(double k) = 0;

protected:
    double x, y;
    double angle;
    Color color;
    int id;
    static int next_id;
};


//Делаем статичекую переменную в классе
int Shape::next_id = 0;

class Regular_hexagon : public Shape
{
public:
    Regular_hexagon(double x, double y, double angle, Color color,double a) : Shape(x, y, angle, color), a(a)
    {}

    virtual ~Regular_hexagon()
    {
    }

    void scaling(double k) override
    {
        a *= k;
    }

    friend std::ostream & operator << (std::ostream & out, Regular_hexagon &hex)
    {
        out << "x1:y1 " << hex.x-hex.a*cos(hex.angle) << " : " << hex.y-hex.a*sin(hex.angle) << endl;
        out << "x2:y2 " << hex.x-hex.a/2*cos(hex.angle) << " : " << hex.y+hex.a*sqrt(3)/2*sin(hex.angle) << endl;
        out << "x3:y3 " << hex.x+hex.a/2*cos(hex.angle) << " : " << hex.y+hex.a*sqrt(3)/2*sin(hex.angle) << endl;
        out << "x4:y4 " << hex.x+hex.a*cos(hex.angle) << " : " << hex.y+hex.a*sin(hex.angle) << endl;
        out << "x5:y5 " << hex.x+hex.a/2*cos(hex.angle) << " : " << hex.y-hex.a*sqrt(3)/2*sin(hex.angle) << endl;
        out << "x6:y6 " << hex.x-hex.a/2*cos(hex.angle) << " : " << hex.y-hex.a*sqrt(3)/2*sin(hex.angle) << endl;
        out << dynamic_cast<Shape &>(hex) << endl << "Side a: " << hex.a;
        return out;
    }
private:
    double a; //side of hexagon
};



class Rectangle : public Shape
{
public:
    Rectangle(double x, double y, double angle, Color color,double a, double b) : Shape(x, y, angle, color), a(a), b(b)
    {}

    virtual ~Rectangle()
    {
    }

    void scaling(double k) override
    {
        a *= k;
        b *= k;
    }

    friend std::ostream & operator << (std::ostream & out, Rectangle &rec)
    {
        out <<  "x1:y1 " << rec.x-(rec.a+rec.b)/2*cos(rec.angle) << " : " << rec.y-(rec.a+rec.b)/2*sin(rec.angle) << endl;
        out <<  "x2:y2 " << rec.x+(rec.a-rec.b)/2*cos(rec.angle) << " : " << rec.y+(rec.a-rec.b)/2*sin(rec.angle) << endl;
        out <<  "x3:y3 " << rec.x+(rec.a+rec.b)/2*cos(rec.angle) << " : " << rec.y+(rec.a+rec.b)/2*sin(rec.angle) << endl;
        out <<  "x4:y4 " << rec.x-(rec.a-rec.b)/2*cos(rec.angle) << " : " << rec.y-(rec.a-rec.b)/2*sin(rec.angle) << endl;
        out << dynamic_cast<Shape &>(rec) << endl << "Side a: " << rec.a << endl <<  "Side b:" << rec.b;
        return out;
    }
private:
    double a; //side a
    double b; //side b
};


class Parallelogram : public Shape
{
public:
    Parallelogram(double x, double y, double angle, Color color, double a, double b, double sides_angle) : Shape(x, y, angle, color), a(a), b(b),sides_angle(sides_angle)
    {}

    virtual ~Parallelogram()
    {
    }

    void scaling(double k) override
    {
        a *= k;
        b *= k;
    }

    friend std::ostream & operator << (std::ostream & out, Parallelogram &par)
    {
        out <<  "x1:y1 " << par.x-(par.a*cos(par.sides_angle)+par.b)/2*cos(par.angle) << " : " << par.y-(par.a*sin(par.sides_angle)+par.b)/2*sin(par.angle) << endl;
        out <<  "x2:y2 " << par.x+(par.a*cos(par.sides_angle)-par.b)/2*cos(par.angle) << " : " << par.y+(par.a*sin(par.sides_angle)-par.b)/2*sin(par.angle) << endl;
        out <<  "x3:y3 " << par.x+(par.a*cos(par.sides_angle)+par.b)/2*cos(par.angle) << " : " << par.y+(par.a*sin(par.sides_angle)+par.b)/2*sin(par.angle) << endl;
        out <<  "x4:y4 " << par.x-(par.a*cos(par.sides_angle)-par.b)/2*cos(par.angle) << " : " << par.y-(par.a*sin(par.sides_angle)-par.b)/2*sin(par.angle) << endl;
        out << dynamic_cast<Shape &>(par) << endl << "Side a: " << par.a << endl << "Side b: " << par.b << endl <<  "Angle between sides: " << par.sides_angle << endl;
        return out;
    }
private:
    double a;
    double b;
    double sides_angle; //angle betweend sides a and b
};

int main()
{
    Rectangle *shape = new Rectangle(10, 4, 41.17, Color::VIOLET, 7, 8);
    cout << *shape << endl;
    shape->scaling(3.4);
    shape->move(1.3, 6);
    shape->rotate(75.45);
    shape->col(Color::RED);
    cout << *shape << endl << endl;
    Parallelogram *p = new Parallelogram(2.59, 35.44, 134.4464, Color::GREEN, 52.134, 71.7834, 72.54);
    cout << *p << endl << endl;
    Regular_hexagon *hex = new Regular_hexagon(1, 1, 21.56, Color::RED, 3);
    cout << *hex << endl;
    hex->scaling(7);
    hex->move(1, 10);
    hex->rotate(771.85);
    hex->col(Color::VIOLET);
    cout << *hex << endl;
    delete shape;
    delete p;
    delete hex;
    return 0;
}
