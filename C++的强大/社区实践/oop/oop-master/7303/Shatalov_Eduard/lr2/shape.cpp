#include "shape.h"
#include <math.h>
int Shape::id_counter = 0;
void Shape::setCoordinates(double newX, double newY) {
    s_x = newX;
    s_y = newY;
}
;
void Shape::setColor(const Color& newColor)
{
    s_color = newColor;
}

const Color Shape::getColor(){
    return s_color;
}

void Shape::rotate(double angle) {
    rotation_angle += angle;
}

int Shape::get_id(){
    return id;
}


