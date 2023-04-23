#include "rgb.h"

void rgb::setColor(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

int rgb::getRed() const
{
    return red;
}

int rgb::getGreen() const
{
    return green;
}

int rgb::getBlue() const
{
    return blue;
}
