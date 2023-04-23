#include "Circle.h"

Circle::Circle(std::vector<Point> &coord, Point &center) {
    for (int i = 0; coord.size() && i < coord.size(); ++i) {
        this->coord.push_back(coord[i]);
    }
    this->center.x = center.x;
    this->center.y = center.y;
    this->calculateArea();
}

void Circle::draw() {
    std::cout << "Info about circle: " << std::endl;
    for (int i = 0; i < this->coord.size(); ++i) {
        std::cout << this->coord[i].x << " : " << this->coord[i].y << std::endl;
    }
    std::cout << "center x: " << this->center.x << ", y: " << this->center.y << std::endl;
    std::cout << "area of circle: " << this->area << std::endl;
}

void Circle::moveTo() {
    this->coord.clear();
    Point temp;
    std::cout << "Input 2 coords of circle (x, y): " << std::endl;
    for (int i = 0; i < 2; ++i) {
        std::cin >> temp.x;
        std::cin >> temp.y;
        this->coord.push_back(temp);
    }
    std::cout << "Input coords of center (x, y): " << std::endl;
    std::cin >> this->center.x;
    std::cin >> this->center.y;
}

void Circle::rotateOn(double angle) {
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

void Circle::scaleOn(double coef) {
    for (int i = 0; i < this->coord.size(); ++i) {
        this->coord[i].x *= coef;
        this->coord[i].y *= coef;
    }
    this->center.x *= coef;
    this->center.y *= coef;
}

void Circle::calculateArea() {
    // находим диагональ, так как наши две точки отвечают именно за нее
    double diagonal = sqrt(pow(this->coord[0].x - this->coord[1].x, 2.0) +
                        pow(this->coord[0].y - this->coord[1].y, 2.0));

    std::cout << "diagonal = " << diagonal << std::endl;
    std::cout << "PI = " << 3.1415 << std::endl;
    // и по школьной формуле находим площадь
    this->area = pow( (diagonal / 2), 2.0 ) * 3.1415;
}