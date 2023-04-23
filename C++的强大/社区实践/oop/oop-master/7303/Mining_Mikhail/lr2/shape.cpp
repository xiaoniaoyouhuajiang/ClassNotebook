#include "shape.h"

unsigned Shape::id = 0;

Shape::Shape(Point center)
{
    id++;
    clr = NOCOLOR;
    centre.x = center.x;
    centre.y = center.y;
}

Color Shape::get_color() const
{
    return clr;
}

void Shape::set_color(Color c)
{
    clr = c;
}

Shape::~Shape()
{
    crd.clear();
}

std::ostream& operator<<(std::ostream& out, Shape& obj)
{
    out << "Shape id: " << obj.id <<  std::endl;
    out << "Shape color: " << obj.get_color() << std::endl;
    out << "Centre coordinates: (" << obj.centre.x << ", " << obj.centre.y << ")\n";
    out << "Points coorditates: ";
    for(unsigned i=0; i<obj.crd.size(); ++i)
        out << '(' << obj.crd[i].x << ", " << obj.crd[i].y << ") ";
    out << std::endl;

    obj.print(out);
}
