#include "Color.h"

Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue) {}

int Color::getRed() const {
    return red;
}

int Color::getGreen() const {
    return green;
}

int Color::getBlue() const {
    return blue;
}
