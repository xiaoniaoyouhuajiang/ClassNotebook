#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

template <typename T>
struct Point {
    T x; T y;
    Point<T>& operator=(const Point<T>& other) { x = other.x; y = other.y; return *this; }
    Point<T>& operator+=(const Point<T>& p) { x += p.x; y += p.y; return *this; }
    Point<T>& operator-=(const Point<T>& p) { x -= p.x; y -= p.y; return *this; }
};

template<typename T>
Point<T> operator+(const Point<T>& lhs, const Point<T>& rhs) { Point<T> temp = {lhs.x + rhs.x, lhs.y + rhs.y}; return temp; }

template<typename T>
Point<T> operator-(const Point<T>& lhs, const Point<T>& rhs) { Point<T> temp = {lhs.x - rhs.x, lhs.y - rhs.y}; return temp; }

template<typename T>
Point<T> operator*(const T& val, const Point<T>& p) { Point<T> temp = {p.x*val, p.y*val}; return temp; }

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Point<T>& point) {
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
}

typedef Point<double> Point2D;

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class Shape
{
public:
    Shape(Point2D, size_t);

    Shape& move_to(Point2D);
    Shape& scale(double);
    Shape& rotate(double);
    Shape& set_color(Color);

    size_t get_total_vertices() const;
    Point2D get_vertex(size_t) const;
    Point2D get_center() const;
    Color get_color() const;

    ~Shape() { delete[] vertex; }

    size_t get_id() const;

protected:
    static size_t TotalShapesCreated;
    const size_t id;
    const size_t v_total;
    Color color;
    Point2D* vertex;
};

size_t Shape::TotalShapesCreated = 0;

Shape::Shape(Point2D pos, size_t vt)
    : id(TotalShapesCreated)
    , v_total(vt+1)
    , vertex(new Point2D[v_total+1]())
{
    vertex[0] = pos;
    TotalShapesCreated++;
    color = Color({0, 0, 0});
}

size_t Shape::get_total_vertices() const
{
    return v_total;
}

Point2D Shape::get_vertex(size_t index) const
{
    return vertex[index];
}

size_t Shape::get_id() const
{
    return id;
}

Point2D Shape::get_center() const
{
    return vertex[0];
}

Color Shape::get_color() const
{
    return color;
}

Shape& Shape::set_color(Color c)
{
    color = c;
}

Shape& Shape::move_to(Point2D pos)
{
    Point2D delta = pos - vertex[0];
    for (size_t i = 0; i < get_total_vertices(); i++) vertex[i] += delta;
    return *this;
}

Shape& Shape::scale(double factor)
{
    Point2D delta;
    for (size_t i = 1; i < get_total_vertices(); i++)
    {
        delta = vertex[i]-vertex[0];
        vertex[i] = vertex[0] + factor*delta;
    }
    return *this;
}

Shape& Shape::rotate(double angle)
{
    Point2D delta;
    for (size_t i = 1; i < get_total_vertices(); i++)
    {
        delta = vertex[i] - vertex[0];
        vertex[i].x = vertex[0].x + delta.x*cos(angle) - delta.y*sin(angle);
        vertex[i].y = vertex[0].y + delta.x*sin(angle) + delta.y*cos(angle);
    }
    return *this;
}

// ***********************************************

class Trapezoid : public Shape
{
public:
    Trapezoid(Point2D, double, double, double, double, double);
};

Trapezoid::Trapezoid(Point2D pos, double height = 1.0, double top = 1.0, double bottom = 1.0, double delta = 0.0, double angle = 0.0)
    : Shape(pos, 4)
    {
        vertex[1] = vertex[0] + Point2D({ top/2.0+delta,  height/2.0});
        vertex[2] = vertex[0] + Point2D({-top/2.0+delta,  height/2.0});
        vertex[3] = vertex[0] + Point2D({   -bottom/2.0, -height/2.0});
        vertex[4] = vertex[0] + Point2D({    bottom/2.0, -height/2.0});
        rotate(angle);
    }

class IsoscelesTrapezoid : public Trapezoid
{
public:
    IsoscelesTrapezoid(Point2D, double, double, double, double);
};

IsoscelesTrapezoid::IsoscelesTrapezoid(Point2D pos, double height = 1.0, double top = 1.0, double bottom = 1.0, double angle = 0.0)
    : Trapezoid(pos, height, top, bottom, 0.0,angle)
{

}

class Ellipse : public Shape
{
public:
    Ellipse(Point2D, double, double, double);
};

Ellipse::Ellipse(Point2D pos, double width = 1.0, double height = 1.0, double angle = 0.0)
    : Shape(pos, 2)
{
    vertex[1] = vertex[0] + Point2D({width,    0.0});
    vertex[2] = vertex[0] + Point2D({  0.0, height});
    rotate(angle);
}

std::ostream& operator<<(std::ostream& stream, const Shape& shape)
{
    stream << "Shape: [ ID=" << shape.get_id() << " ";
    stream << "Center=" << shape.get_center() << " ";
    for (size_t i = 1; i < shape.get_total_vertices(); i++) stream << "Vertex#" << i << "=" << shape.get_vertex(i) << " ";
    stream << "]";
}

#endif // SHAPE_H_INCLUDED
