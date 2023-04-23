#include "Rectangle.h"

Rectangle::Rectangle(std::vector<Point> &coord, Point &center) {
    for (int i = 0; coord.size() && i < coord.size(); ++i) {
        this->coord.push_back(coord[i]);
    }
    this->center.x = center.x;
    this->center.y = center.y;
    this->calculateArea();
}

void Rectangle::draw() {
    std::cout << "Info about rectangle: " << std::endl;
    for (int i = 0; i < this->coord.size(); ++i) {
        std::cout << this->coord[i].x << " : " << this->coord[i].y << std::endl;
    }
    std::cout << "center x: " << this->center.x << ", y: " << this->center.y << std::endl;
    std::cout << "area of rectangle: " << this->area << std::endl;
}

void Rectangle::moveTo() {
    this->coord.clear();
    Point temp;
    std::cout << "Input 3 coords of rectangle (x, y): " << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cin >> temp.x;
        std::cin >> temp.y;
        this->coord.push_back(temp);
    }
    std::cout << "Input coord of center (x, y): " << std::endl;
    std::cin >> this->center.x;
    std::cin >> this->center.y;
}

void Rectangle::rotateOn(double angle) {
    double x_help = this->center.x;
    double y_help = this->center.y;
    this->center.x = (x_help * cos(angle)) - (y_help * sin(angle));
    this->center.y = (x_help * sin(angle)) + (y_help * cos(angle));
    for (int i = 0; i < this->coord.size(); ++i) {
        x_help = this->coord[i].x;
        y_help = this->coord[i].y;
        this->coord[i].x = (x_help * cos(angle)) - (y_help * sin(angle));
        this->coord[i].y = (x_help * sin(angle)) + (y_help * cos(angle));
    }
}

void Rectangle::scaleOn(double coef) {
    for (int i = 0; i < this->coord.size(); ++i) {
        this->coord[i].x *= coef;
        this->coord[i].y *= coef;
    }
    this->center.x *= coef;
    this->center.y *= coef;
}

void Rectangle::calculateArea() {
    double sides[3] = {0};
    double semiPerimetr = 0;

    // находим длины трех сторон
    sides[0] = sqrt(pow(this->coord[0].x - this->coord[1].x, 2.0) +
                    pow(this->coord[0].y - this->coord[1].y, 2.0));
    sides[1] = sqrt(pow(this->coord[0].x - this->coord[2].x, 2.0) +
                    pow(this->coord[0].y - this->coord[2].y, 2.0));
    sides[2] = sqrt(pow(this->coord[1].x - this->coord[2].x, 2.0) +
                    pow(this->coord[1].y - this->coord[2].y, 2.0));

    // определяем полупериметр
    for (int i = 0; i < this->coord.size(); ++i) {
        semiPerimetr += sides[i];
    }
    semiPerimetr /= 2;
    std::cout << "semiper = " << semiPerimetr << std::endl;

    // находим площадь через стороны и полупериметр
    this->area = sqrt(semiPerimetr * (semiPerimetr - sides[0]) *
                              (semiPerimetr - sides[1]) * (semiPerimetr - sides[2]));
}