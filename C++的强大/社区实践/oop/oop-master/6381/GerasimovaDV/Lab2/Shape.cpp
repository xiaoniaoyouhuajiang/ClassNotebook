#include "Shape.h"


void Shape::move(Point* point) {
    float x_offset = point->x() - getCenterPoint()->x();
    float y_offset = point->y() - getCenterPoint()->y();
    for(Point* current : points) {
        current->x() += x_offset;
        current->y() += y_offset;
    }
}

void Shape::rotate(float angle) {
    Point* center = getCenterPoint();
    float c_x = center->x();
    float c_y = center->y();
    float x, y;
    for(Point* current : points) {
        current->x() -= center->x();
        current->y() -= center->y();
        x = current->x() * cos(angle) - current->y() * sin(angle) + c_x;
        y = current->x() * sin(angle) + current->y() * cos(angle) + c_y;
        current->x() = x;
        current->y() = y;
    }
}

void Shape::scale(float factor) {
    Point* center = getCenterPoint();
    float x = center->x();
    float y = center->y();
    for(Point* current : points) {
        current->x() = (current->x() - center->x()) * factor + x;
        current->y() = (current->y() - center->y()) * factor + y;
    }

}


Color* Shape::getColor() const {
    return color;
}

int Shape::getId() const {
    return id;
}

vector<Point*>& Shape::getPoints() {
    return points;
}
