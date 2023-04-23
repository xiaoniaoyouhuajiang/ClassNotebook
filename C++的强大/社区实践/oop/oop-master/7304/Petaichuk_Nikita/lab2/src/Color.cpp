#include "Color.h"

Color::Color(unsigned int red, unsigned int green, unsigned int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

Color::Color(const Color &other) :
  red(other.getRedComponent()),
  blue(other.getBlueComponent()),
  green(other.getGreenComponent())
{
}

Color& Color::operator=(const Color &other)
{
    if (this != &other)
    {
        red = other.getRedComponent();
        blue = other.getBlueComponent();
        green = other.getGreenComponent();
    }
    return *this;
}

void Color::setRedComponet(unsigned int red)
{
    this->red = red;
}

void Color::setGreenComponet(unsigned int green)
{
    this->green = green;
}

void Color::setBlueComponet(unsigned int blue)
{
    this->blue = blue;
}

unsigned int Color::getRedComponent() const
{
    return red;
}

unsigned int Color::getGreenComponent() const
{
    return green;
}

unsigned int Color::getBlueComponent() const
{
    return blue;
}

ostream& operator<<(ostream &os, const Color &color)
{
    os << "Color:" << endl
    << "    -) Red: " << color.red << endl
    << "    -) Green: " << color.green << endl
    << "    -) Blue: " << color.blue << endl;
    return os;
}
