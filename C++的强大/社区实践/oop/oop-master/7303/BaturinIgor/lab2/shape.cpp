#include "shape.h"

int Shape::global_id = 0;

Shape::Shape() : id(global_id)
{
    global_id++;
}

Shape::Shape(Color &color)
    : color(color)
{

}

Color Shape::getColor() {
    return color;
}

void Shape::setColor(const Color& newColor) {
    color = newColor;
}

int Shape::getID() const{
    return id;
}