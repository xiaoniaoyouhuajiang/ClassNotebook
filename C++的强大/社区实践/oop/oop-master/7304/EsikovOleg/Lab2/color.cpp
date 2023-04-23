#include "color.h"

Color& Color::operator = (const Color& element)
{
    red = element.red;
    green = element.green;
    blue = element.blue;
    return *this;
}

void operator << (ostream& os, const Color& element)
{
    os << "Red: " << element.red << " Green: " << element.green << " Blue: " << element.blue << std::endl;
}
