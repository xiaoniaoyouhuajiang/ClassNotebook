#ifndef ETUOOP_SHAPES_H
#define ETUOOP_SHAPES_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <exception>
#include <functional>

namespace etuoop
{

struct Point {
    double x;
    double y;
    Point(double x = 0, double y = 0):
        x(x), y(y)
    {}
};

class Shape
{
public:
    virtual Shape* clone() const = 0;
    virtual ~Shape() {}
    static Shape* createRandom(std::initializer_list< std::function<Shape*()> > childCreators);
    void setColor(unsigned int color)
    {
        this->color = color;
    }
    unsigned int getColor() const
    {
        return this->color;
    }
    void setPosition(Point pos)
    {
        this->pos = pos;
    }
    Point getPosition() const
    {
        return this->pos;
    }
    void setAngle(double angle)
    {
        this->angle = fmod(angle, 2 * M_PI);
    }
    double getAngle() const
    {
        return this->angle;
    }
    virtual void stretch(double q) = 0;
    unsigned int getId() const
    {
        return this->id;
    }
    virtual std::ostream& print(std::ostream& stream) const
    {
        stream << "at [" << pos.x << ";" << pos.y << "], angle [" << angle << "], "
               << "color [" << std::setw(8) << std::setfill('0') << std::hex << color << "], "
               << "id [" << std::dec << id << "]";
        return stream;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Shape& shape)
    {
        return shape.print(stream);
    }

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;

    class ConstructError: public std::logic_error
    {
    public:
        using std::logic_error::logic_error;
    };

    class IllegalMethod: public std::logic_error
    {
    public:
        using std::logic_error::logic_error;
    };

protected:
    Shape(Point pos = Point(),
          double angle = 0, unsigned int color = 0x000000FF)
        : pos(pos),
          color(color),
          id(++counter)
    {
        setAngle(angle);
    }
    Shape(const Shape& other):
        pos(other.pos),
        angle(other.angle),
        color(other.color),
        id(++counter)
    {
    }

private:
    static unsigned int counter;
    const unsigned int id;
protected:
    Point pos;
    double angle;
    unsigned int color;
};

class Rectangle: public Shape
{
public:
    static Rectangle* createRandom();
    Rectangle(double length, double width,
              Point pos = Point(),
              double angle = 0, unsigned int color = 0x000000FF)
        : length(length), width(width),
          Shape(pos, angle, color)
    {
        if (length <= 0) {
            throw Shape::ConstructError("Incorrect length");
        }
        if (width <= 0) {
            throw Shape::ConstructError("Incorrect width");
        }
    }

    virtual Rectangle* clone() const
    {
        return new Rectangle(*this);
    }

    double getLength() const
    {
        return this->length;
    }

    double getWidth() const
    {
        return this->width;
    }

    void stretch(double q) override
    {
        if (q <= 0) {
            throw Shape::IllegalMethod("Stretch coeff must be non-negative");
        }
        this->length *= q;
        this->width *= q;
    }

    virtual void stretchWidth(double q)
    {
        if (q <= 0) {
            throw Shape::IllegalMethod("Stretch coeff must be non-negative");
        }
        this->width *= q;
    }

    virtual void stretchLength(double q)
    {
        if (q <= 0) {
            throw Shape::IllegalMethod("Stretch coeff must be non-negative");
        }
        this->length *= q;
    }

    double getArea() const override
    {
        return length * width;
    }
    double getPerimeter() const override
    {
        return 2 * (length + width);
    }

    std::ostream& print(std::ostream& stream) const override
    {
        stream << "Rectangle [" << length << "x" << width << "] ";
        Shape::print(stream);
        return stream;
    }

protected:
    double length;
    double width;
};

class Square: public Rectangle
{
public:
    Square(double side,
           Point pos = Point(),
           double angle = 0, unsigned int color = 0x000000FF)
        : Rectangle(side, side, pos, angle, color)
    {
    }

    static Square* createRandom();

    virtual Square* clone() const
    {
        return new Square(*this);
    }

    void stretchLength(double q) override
    {
        throw Shape::IllegalMethod("Can't stretch only length of Square");
    }

    void stretchWidth(double q) override
    {
        throw Shape::IllegalMethod("Can't stretch only width of Square");
    }

    std::ostream& print(std::ostream& stream) const override
    {
        stream << "Square [" << length << "] ";
        Shape::print(stream);
        return stream;
    }
};

class Ellipse: public Rectangle
{
public:
    using Rectangle::Rectangle;

    virtual Ellipse* clone() const
    {
        return new Ellipse(*this);
    }

    static Ellipse* createRandom();

    double getArea() const override
    {
        return M_PI * width * length / 4;
    }
    double getPerimeter() const override
    {
        return (2 * M_PI * width * length + 4 * fabs(width - length)) / (width + length);
    }

    std::ostream& print(std::ostream& stream) const override
    {
        stream << "Ellipse [" << length << "x" << width << "] ";
        Shape::print(stream);
        return stream;
    }
};

unsigned int Shape::counter = 0;

const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine rng(seed);
static const double magicborder = 1 << 8;

Shape* Shape::createRandom(std::initializer_list< std::function<Shape*()> > childCreators)
{
    static const size_t childN = childCreators.size();
    int s = std::uniform_int_distribution<int>(0, childN-1)(rng);
    return (*(childCreators.begin()+s))();
}

Rectangle* Rectangle::createRandom()
{
    return new Rectangle(
               std::uniform_real_distribution<double>(1, magicborder)(rng), // length
               std::uniform_real_distribution<double>(1, magicborder)(rng), // width
               etuoop::Point(
                   std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
                   std::uniform_real_distribution<double>(-magicborder, magicborder)(rng) // y
               ),
               std::uniform_real_distribution<double>(0, 2 * M_PI)(rng), // angle
               std::uniform_int_distribution<unsigned int>(0, 0xFFFFFFFF)(rng) // color
           );
}

Square* Square::createRandom()
{
    return new etuoop::Square(
               std::uniform_real_distribution<double>(1, magicborder)(rng), // side
               etuoop::Point(
                   std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
                   std::uniform_real_distribution<double>(-magicborder, magicborder)(rng) // y
               ),
               std::uniform_real_distribution<double>(0, 2 * M_PI)(rng), // angle
               std::uniform_int_distribution<unsigned int>(0, 0xFFFFFFFF)(rng) // color
           );
}

Ellipse* Ellipse::createRandom()
{
    return new etuoop::Ellipse(
               std::uniform_real_distribution<double>(1, magicborder)(rng), // length
               std::uniform_real_distribution<double>(1, magicborder)(rng), // width
               etuoop::Point(
                   std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
                   std::uniform_real_distribution<double>(-magicborder, magicborder)(rng) // y
               ),
               std::uniform_real_distribution<double>(0, 2 * M_PI)(rng), // angle
               std::uniform_int_distribution<unsigned int>(0, 0xFFFFFFFF)(rng) // color
           );
}

} //namespace etuoop

#endif
