#include "shape.h"

int Shape::nextID = 0;

void operator<<(ostream& os, Shape& argument)
{
    argument.Information(os);
}

void Shape::getColor()
{
    cout << color;
}

void Shape::setColor(Color argument)
{
    color = argument;
}

void Shape::getInfo(ostream& os)
{
    os << "ID: " << ID << endl;
    os << "Centre: " << centre;
    os << "Coefficient of scaling: " << scaled << endl;
    os << "Number of angles: " << angles << endl;
    os << "Color: ";
    getColor();
    os << "Angle of rotation: " << angle << endl;
}
