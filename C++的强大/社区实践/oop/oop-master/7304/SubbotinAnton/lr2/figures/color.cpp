#include "color.h"

Color& Color::operator=(const Color& argument)
{
    red = argument.red;
    green = argument.green;
    blue = argument.blue;
    return *this;
}

void operator<<(ostream& os, const Color& argument)
{
    os << endl << "  Red:   " << argument.red << endl;
    os << "  Green: " << argument.green << endl;
    os << "  Blue:  " << argument.blue << endl << endl;
}
