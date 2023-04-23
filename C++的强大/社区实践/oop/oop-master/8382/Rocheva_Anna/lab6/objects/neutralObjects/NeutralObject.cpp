#include "NeutralObject.hpp"

void NeutralObject::setCoordinates(int x, int y) {
    coordinates = new Coordinates;
    coordinates->x = x;
    coordinates->y = y;
}
