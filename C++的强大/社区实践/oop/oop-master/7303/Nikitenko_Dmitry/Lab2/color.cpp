#include "color.h"

Color::Color() : red(0), green(0), blue(0)
{
}

Color::Color(int r,int g, int b) : red(r), green(g), blue(b)
{
}

Color::Color(Color& color) : red(color.red), green(color.green), blue(color.blue)
{
}

void Color::setColor(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}
void Color::setRed(int red)
{
    this->red = red;
}
void Color::setGreen(int green)
{
    this->green = green;
}
void Color::setBlue(int blue)
{
    this->blue = blue;
}

std::ostream& Color::print(std::ostream& out)
{
    out<<"Red = "<< red;
    out<<" Green = "<< green;
    out<<" Blue = "<< blue<<std::endl;
    return out;
}

std::ostream& operator<< (std::ostream &out, Color& color)
{
    return color.print(out);
}

